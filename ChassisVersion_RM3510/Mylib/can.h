#ifndef _CAN_H_
#define _CAN_H_

#include "stm32f4xx.h"


void GYRO_RST(void);


void CAN1_Configuration(void);
void CAN2_Configuration(void);

//RM3510
void Cmd_ESC_820R(int16_t current_201,int16_t current_202,int16_t current_203,int16_t current_204);
int GetAngleDiff(int16_t lastAngle, int16_t thisAngle);

#endif
