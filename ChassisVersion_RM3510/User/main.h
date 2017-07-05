#ifndef __MAIN_H__
#define __MAIN_H__



//���幤�������ģʽ
//#define DEBUG


//����RM3510��pid
#define ESC_820R_VEL_P 10.0//10.0
#define ESC_820R_VEL_I 0.0
#define ESC_820R_VEL_D 0.5//0.5
#define ESC_820R_POS_P 100.0//10.0
#define ESC_820R_POS_I 0.0
#define ESC_820R_POS_D 0.1


//�����˶��ٶȶ���
 #define NormalSpeed 100
 #define HighSpeed 150
 #define LowSpeed 50


//ʱ��NVIC����
#define MPU6050_Channel EXTI4_IRQn
#define MPU6050_PreemptionPriority 0
#define MPU6050_SubPriority 0

#define HMC5883L_Channel EXTI3_IRQn
#define HMC5883L_PreemptionPriority 0
#define HMC5883L_SubPriority 0

#define CAN1_RX_Channel CAN1_RX0_IRQn
#define CAN1_RX_PreemptionPriority 0
#define CAN1_RX_SubPriority 0

#define CAN1_TX_Channel CAN1_TX_IRQn
#define CAN1_TX_PreemptionPriority 1
#define CAN1_TX_SubPriority 1

#define CAN2_RX_Channel CAN2_RX1_IRQn
#define CAN2_RX_PreemptionPriority 0
#define CAN2_RX_SubPriority 2

#define CAN2_TX_Channel CAN2_TX_IRQn
#define CAN2_TX_PreemptionPriority 0
#define CAN2_TX_SubPriority 0

#define DMA1_Channel DMA1_Stream1_IRQn
#define DMA1_PreemptionPriority 0
#define DMA1_SubPriority 2

#define USART3_Channel USART3_IRQn
#define USART3_PreemptionPriority 3
#define USART3_SubPriority 3

#define DMA2_Channel DMA2_Stream5_IRQn
#define DMA2_PreemptionPriority 0
#define DMA2_SubPriority 1

#define TIM6_Channel TIM6_DAC_IRQn
#define TIM6_PreemptionPriority 3
#define TIM6_SubPriority 2


//�����
#include "stm32f4xx.h"
//��ʼ��
#include "initialization.h"
//DBUS�����ʹ���
#include "dbus.h"
#include "usart1.h"

//CAN1��̨��CAN2���̵��
//#include "can1.h"
//#include "can2.h"
#include "can.h"
//timer2���ڼ�ʱ��
#include "timer.h"

//NVIC
#include "nvic.h"
//���ڵ��Ժ���ROS������Ϣ
#include "usart3.h"
//����
#include "chassis_control.h"
//PID
#include "pid_algorithm.h"
//MPU6050 HMC5883L��
#include "mpu6050_hmc5883l_driver.h"
#include "mpu6050_hmc5883l_i2c.h"
#include "mpu6050_hmc5883l_interrupt.h"
#include "mpu6050_hmc5883l_process.h"
//�������Ժ���ʱ
#include "led.h"
#include "delay.h"
//����
#include "laser.h"
//����������
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
//���sdbus����Э��
#include <sdbus.h>

//���ú��� ȡ���ֵ�;���ֵ
#define abs(x) ((x)>0? (x):(-(x)))
#define maxs(a,b) (a>b? a:b)

//�������ڵ���printf
extern char buffer1[32];

#endif 
