/************************************************************************************
  File Name     :  initialization.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  main�и���ģ��ĳ�ʼ����ע��timerstart�Ϳ�����Ӧ���ֳ�ʼ����λ��
									 

-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			   ��ʼ��	
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					  ע��	
************************************************************************************/
#include "main.h"

void  Initialization(void)
{
	
		int i = 0;//���ڳ�ʼ��mpu6050��hmc5883l
		SystemInit();//ϵͳʱ������
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC���ȼ���2
		
		Led_Configuration();//LED��ʼ��������mpu6050��hmc5883l�ĳ�ʼ����Debug
		Laser_Configuration();//Laser��ʼ��
		USART1_Config();//����1�����ã�DBUS RX��
		USART3_Configuration();//����3�����ã����ڵ��ԣ�
		
		TIM2_Configuration();//���ڼ�ʱ
		CAN1_Configuration();//	Can1�����ã����ڿ��Ƶ���
		CAN2_Configuration();//Can2�����ã����ڿ��� Gimbal

		delay_ms(500);  
		
		/*
		while(MPU6050_Initialization() == 0xff || HMC5883L_Initialization() == 0xff) 
    {
        i++;     //���һ�γ�ʼ��û�гɹ����Ǿ�����һ��                     
        if(i>10) //�����ʼ��һֱ���ɹ����Ǿ�ûϣ���ˣ�������ѭ������ɫLEDһֱ��
        {
            while(1) 
            {
                LED_GREEN_TOGGLE();
                delay_ms(50);
                
            }
        }  
				
				printf("WE failed again~");
    } 
		
    MPU6050_Gyro_calibration();//MPU6050У׼
    
		
		MPU6050_HMC5883L_Interrupt_Configuration(); //HMC��MPU���ж�����
		*/
		
		delay_ms(500);		
		

}
