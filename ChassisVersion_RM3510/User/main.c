/************************************************************************************
  File Name     :  main.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :   main������Ҫ���ڳ���ӿڣ����а�����ʼ�����ֺ͵��̿��Ƽ����䲿�֣�
										main.hͷ�ļ���Ҫ�����˼������п�����ü�ս�����ֲ��������ã�������
										��̨�ĽǶȲ�������̨����PID���������̵�����࣬Ħ���ֵ���ٶ��Լ�
										NVIC�����ã�����һЩ���ú����Ķ��塣
										
  
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   					main����	 ������ʼ�����ֺ͵��̿��Ƽ����䲿��
2     1.2       6/29       gyf 
3     1.3       6/29       yf 						ע��						
************************************************************************************/	
#include "main.h"

char buffer1[32];//���ڴ���printf����Ҫ�����ã�

int main(void)
{   
		
		Initialization();
	
		while(1)
		{	
			LED_RED_ON();
			delay_ms(1000);
			LED_GREEN_OFF();
			delay_ms(1000);
			
			LED_RED_OFF();
			delay_ms(1000);
			LED_GREEN_ON();
			delay_ms(1000);
				
				
				
			//���ڲ�������
			//delay_ms(50);
			//printf("%d,%d\n",RM3510_1.thisPosition,RM3510_2.thisPosition);
			//printf("%d,%d\n",RM3510_1.targetVelocity,RM3510_1.thisVelocity);
			//printf("%d\n",Get_Time_Micros());
			//printf(buffer1);
			
			
			
			printf("\n\r\n\r\n\rStatusDemo: \n\rWheel1:%12.6f,%5d; \n\rWheel2:%12.6f,%5d; \n\rWheel3:%12.6f,%5d; \n\rWheel4:%12.6f,%5d;\n\r\n\r\n\r", \
			RM3510_1.thisPosition,RM3510_1.thisVelocity,RM3510_2.thisPosition,RM3510_2.thisVelocity,RM3510_3.thisPosition,RM3510_3.thisVelocity,RM3510_4.thisPosition,RM3510_4.thisVelocity);
			delay_ms(1000);
			
			printf("\n\r\n\r\n\rDBUS:%d,%d,%d,%d,%d,%d\n\r\n\r\n\r", dbus.rc.ch0, dbus.rc.ch1, dbus.rc.ch2, dbus.rc.s1, dbus.key.v,dbus.mouse.x);
			//printf("A");




		//	int	g=GetQuadEncoderDiff();
				//	ShootMotorSpeedSet((int)Velocity_Control_Shoot(g,10));
			//	sprintf(buffer1,"%d %d\n",g,PWM3);
				//sprintf(buffer1,"%d %d\n",Yaw.thisAngle,Pitch.thisAngle);
			//	printf(buffer1);
				
		}
}


