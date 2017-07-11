/************************************************************************************
  File Name     :  pid_algorithm.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ��̨pitch��206����yaw��205�����ٶȻ���λ�û���pid�㷨��
									 RM3510���820R����ĵ��ٶȻ���λ�û���pid�㷨
									 

-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			  pid�㷨	
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					  ע��	
4			1.4       7/1				 yf     Velocity_Control_Shoot  ��������ٶȻ�PID          
************************************************************************************/
#include "main.h"

//#define GAP 0.0

/*
WE are using the `static` value in each function as the `global` variables, so if we want to reset the PID, we should reset the static values.
It is kind of ugly.

*/


/********************************************************************************
                           820R��������ٶȻ�����
                      ���� 820R�ᵱǰ�ٶ� 820R��Ŀ���ٶ�
*********************************************************************************/
float _Velocity_Control_820R(float current_velocity_820R,float target_velocity_820R, int num ,int reset)
{
    const float l_p = ESC_820R_VEL_P;//7.0
    const float l_i = ESC_820R_VEL_I;//0.5
    const float l_d = ESC_820R_VEL_D;

    static float error_l[4][2] = {0.0,0.0, 0.0,0.0, 0.0,0.0, 0.0,0.0};
    static float inte[4] = {0.0, 0.0, 0.0, 0.0};
    
		float output = 0;
 
		num = num -1; // correct num
		
		if (reset == 1) {
			int i = 0;
			for(;i < 4; i++){
				error_l[i][0] = 0.0;
				error_l[i][1] = 0.0;
				inte[i] = 0.0;
			}
			return 0.0; // Just return is OK
		}
		
    error_l[num][0] = error_l[num][1];
    error_l[num][1] = target_velocity_820R - current_velocity_820R;
    inte[num] += error_l[num][1]; 
    
    output = error_l[num][1] * l_p 
            + inte[num] * l_i 
            + (error_l[num][1] - error_l[num][0]) * l_d;
		
    
    if(output > ESC_MAX_VEL)
    {
        output = ESC_MAX_VEL;
    }
    
    if(output < -ESC_MAX_VEL)
    {
        output = -ESC_MAX_VEL;
    }
    		
    return output;
}


float Velocity_Control_820R(float current_velocity_820R,float target_velocity_820R, int motorNum)
{
	return _Velocity_Control_820R(current_velocity_820R, target_velocity_820R, motorNum, 0);
}

void Velocity_Control_820R_RESET(void)
{
	_Velocity_Control_820R(0.0, 0.0, 0, 1);
}


/********************************************************************************
                           820R������λ�û�����
                      ���� 820R�ᵱǰλ�� 820R��Ŀ��λ��
*********************************************************************************/
float _Position_Control_820R(float current_position_820R,float target_position_820R, int num, int reset)
{
    const float l_p = ESC_820R_POS_P;
		const float l_i = ESC_820R_POS_I;
		const float l_d = ESC_820R_POS_D;
    static float error_l[4][2] = {0.0,0.0, 0.0,0.0, 0.0,0.0, 0.0,0.0};
    static float inte[4] = {0.0, 0.0, 0.0, 0.0};
    
		float output = 0;
    
		num = num -1; // correct num
		
		if (reset == 1) {
			int i = 0;
			for(;i < 4; i++){
				error_l[i][0] = 0.0;
				error_l[i][1] = 0.0;
				inte[i] = 0.0;
			}
			return 0.0; // Just return is OK
		}
		
    error_l[num][0] = error_l[num][1];
    error_l[num][1] = target_position_820R - current_position_820R;
    inte[num] += error_l[num][1]; 
    
    output = error_l[num][1] * l_p 
            + inte[num] * l_i 
            + (error_l[num][1] - error_l[num][0]) * l_d;
    
    if(output > ESC_MAX_POS)
    {
        output = ESC_MAX_POS;
    }
    
    if(output < -ESC_MAX_POS)
    {
        output = -ESC_MAX_POS;
    }
    		
    return output;
}

float Position_Control_820R(float current_position_820R,float target_position_820R, int motorNum)
{
	return _Position_Control_820R(current_position_820R,target_position_820R, motorNum, 0);
}

void Position_Control_820R_RESET(void)
{
	_Position_Control_820R(0.0, 0.0, 0, 1);
}
