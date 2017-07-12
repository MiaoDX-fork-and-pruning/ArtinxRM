/************************************************************************************
  File Name     :  timer.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  timer�����ã�ռ��TIMER6��TIMER2��TIMER3��
									 //Timer 2 32-bit counter (Regard as time counter) 
									 //Timer Clock is 180MHz / 4 * 2 = 90M
									 ����timer6�����жϿ�����̨��ʱ��Ϊ100/90ms��
									 timer2��������ʱ����ʱ��Ϊ1MHz��
									 ��Ҫע�����timer���жϿ��Ƶģ���Ҫ���жϿ���ʹ�ܷ���main��ʼ���ĺ���
									 
-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			 timer���ú���	����TIM��ʼ�����жϼ�nvic������
2     1.2       6/29       gyf 				 �޸�timer6�ж�ʱ�䣬����timer3�ж�
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
#include "main.h"

void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    tim.TIM_Period = 0xFFFFFFFF;
    tim.TIM_Prescaler = 90 - 1;	 //1M ��ʱ��  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM2, ENABLE);	
    TIM_TimeBaseInit(TIM2, &tim);

    TIM_Cmd(TIM2,ENABLE);	
}
void TIM2_IRQHandler(void)
{
	 // printf("in!\n");
	  if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
			  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			  LED_RED_TOGGLE();
		}
} 

uint32_t Get_Time_Micros(void)
{
	return TIM2->CNT;
}
