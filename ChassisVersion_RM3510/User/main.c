/************************************************************************************
  File Name     :  main.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :   main函数主要用于程序接口，其中包含初始化部分和地盘控制及发射部分；
										main.h头文件主要包括了几乎所有库的引用及战车各种参数的配置，包括了
										云台的角度参数，云台整定PID参数，底盘电机种类，摩擦轮电机速度以及
										NVIC的配置，还有一些常用函数的定义。
										
  
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   					main函数	 包含初始化部分和地盘控制及发射部分
2     1.2       6/29       gyf 
3     1.3       6/29       yf 						注释						
************************************************************************************/	
#include "main.h"

char buffer1[32];//用于串口printf，主要调试用；

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
				
				
				
			//串口测试例子
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


