/************************************************************************************
  File Name     :  mpu6050_hmc5883l_interrupt.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ����mpu6050��hmc5883l�Ľ�������GPIO�����ⲿ�ж�
										----mpu6050-----PA4-----EXTI4----
										----hmc5883-----PA3-----EXTI3----
									 
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       								Description   
1     1.1       6/28       yf   		EXTI4_IRQHandler      	��mpu6050���ж�����6050���ݽ��ռ�rm3510����ĵ��̿��ƺ���̨����
																		EXTI3_IRQHandler				��hmc5883l���ж����ܵش����ݽ��պ�ahrs�㷨ȷ��ʵʱq��ŷ����
2     1.2       6/29       gyf 			EXTI4_IRQHandler        ��mpu6050�ж���ֻ��6050���ݽ��ռ�rm3510����ĵ��̿��ƣ���̨�����ƶ���timer6����         
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
#include "main.h"
uint32_t a=0;//debugʱ��
void MPU6050_HMC5883L_Interrupt_Configuration(void)
{
    GPIO_InitTypeDef    gpio;
    EXTI_InitTypeDef    exti;
 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);   
 
	  gpio.GPIO_Pin = GPIO_Pin_4;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &gpio);
	
		gpio.GPIO_Pin = GPIO_Pin_3;
		GPIO_Init(GPIOA, &gpio);
    
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,GPIO_PinSource3); 
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,GPIO_PinSource4); 
		
    exti.EXTI_Line = EXTI_Line4;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;//�½����ж�
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
		
		exti.EXTI_Line = EXTI_Line3;
    EXTI_Init(&exti);
		
		NVIC_Set(MPU6050_Channel,MPU6050_PreemptionPriority,MPU6050_SubPriority,ENABLE);
	//	NVIC_Set(HMC5883L_Channel,HMC5883L_PreemptionPriority,HMC5883L_SubPriority,ENABLE);

}

//MPU6050 �ⲿ�жϴ�����
void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        //2ms���ж�һ��
        //��ȡMPU6050����,Ϊ��ʹ��̨�Ŀ��Ƹ�ƽ����
        //ʹ��MPU6050�������������Ϊ�ٶȻ�����
        //����ʹ�õ���巵�ػ�е�Ƕ�ֵ���ٶȻ���������������������
        
				MPU6050_ReadData();//��ȡδ�˲�����                                              
        MPU6050_Data_Filter();//��Ҫ��mpu6050���ٶȼƵľ�ֵ�˲��������ǻ�����ת��
				
				printf("\nMPU6050 iteruption ... \n");
				
				if(DBUS_Det(dbus))//rc�����ж�
				{		
						if(dbus.rc.s2==2){
							move_control(dbus.rc.ch0, dbus.rc.ch1, dbus.rc.ch2, dbus.rc.s1, dbus.key.v,dbus.mouse.x);			
						}
						else if(dbus.rc.s2==1){
							ChassisMotor_Position_Control(sdbus.w1,sdbus.w2,sdbus.w3,sdbus.w4);
						}
						else if(dbus.rc.s2==3){
							RM3510_1.thisPosition=0;
							RM3510_2.thisPosition=0;
							RM3510_3.thisPosition=0;
							RM3510_4.thisPosition=0;
							sdbus.w1=0;
							sdbus.w2=0;
							sdbus.w3=0;
							sdbus.w4=0;
						}
				}
			
				
				//sprintf(buffer1,"%d \n",Get_Time_Micros()-a);
				//a=Get_Time_Micros();
				
				
				
				
				EXTI_ClearFlag(EXTI_Line4);          
				EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) == SET)
    {
        //75hz-13ms���ж�һ�Σ�NOT USED����30hz-33ms���ж�һ��
        HMC5883L_ReadData();
				//AHRS����
				AHRS_Calculate( 				 Gyro_Radian_Data.X,
																 Gyro_Radian_Data.Y,
																 Gyro_Radian_Data.Z,
																 MPU6050_Real_Data.Accel_X,
																 MPU6050_Real_Data.Accel_Y,
																 MPU6050_Real_Data.Accel_Z,
																 HMC5883L_Real_Data.Mag_X,
																 HMC5883L_Real_Data.Mag_Y,
																 HMC5883L_Real_Data.Mag_Z);
				
				//sprintf(buffer1,"%f \r %f \r %f \n",AHRS_Data.Pos_Nav_x,AHRS_Data.Pos_Nav_y,AHRS_Data.Pos_Nav_z);
				//sprintf(buffer1,"%f \r %f \r %f \n",AHRS_Data.Vel_Nav_x,AHRS_Data.Vel_Nav_y,AHRS_Data.Vel_Nav_z);
				//printf(buffer1);
				//sprintf(buffer1,"%d \r %d \r %d \n",HMC5883L_Raw_Data.Mag_X,HMC5883L_Raw_Data.Mag_Y,HMC5883L_Raw_Data.Mag_Z);
				//sprintf(buffer1,"%f \n",HMC5883L_Real_Data.Yaw_Angle);
				//printf(buffer1);
				//delay_ms(100);
				
				EXTI_ClearFlag(EXTI_Line3);          
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

