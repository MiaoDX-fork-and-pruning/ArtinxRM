#ifndef __PID_ALGORITHM_H__
#define __PID_ALGORITHM_H__
#include <stm32f4xx.h>

#define ESC_MAX_POS 1000.0
#define ESC_MAX_VEL 1000.0

float Velocity_Control_820R(float current_velocity_820R,float target_velocity_820R, int motorNum);
float Position_Control_820R(float current_position_820R,float target_position_820R, int motorNum);

void Velocity_Control_820R_RESET(void);
void Position_Control_820R_RESET(void);

#endif
