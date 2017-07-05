#include "main.h"

/*----CAN1_TX-----PD1----*/
/*----CAN1_RX-----PD0----*/


/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/

void CanReceiveMsgProcess(CanRxMsg *rx_message); // declare first

void CAN1_Configuration(void)
{
		CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOD, &gpio);
    
    nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = CAN1_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);    
    
    CAN_DeInit(CAN1);
    CAN_StructInit(&can);
    
    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;
    can.CAN_AWUM = DISABLE;
    can.CAN_NART = DISABLE;
    can.CAN_RFLM = DISABLE;
    can.CAN_TXFP = ENABLE;
    can.CAN_Mode = CAN_Mode_Normal;
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_5tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 45/(1+9+5)/3=1Mbps
    CAN_Init(CAN1, &can);

	  can_filter.CAN_FilterNumber=0;
	  can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	  can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	  can_filter.CAN_FilterIdHigh=0x0000;
	  can_filter.CAN_FilterIdLow=0x0000;
	  can_filter.CAN_FilterMaskIdHigh=0x0000;
	  can_filter.CAN_FilterMaskIdLow=0x0000;
	  can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
	  can_filter.CAN_FilterActivation=ENABLE;
	  CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
}

void GYRO_RST(void)
{
    CanTxMsg tx_message;
    
    tx_message.StdId = 0x404;//send to gyro controll board
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = 0x00;
    tx_message.Data[1] = 0x01;
    tx_message.Data[2] = 0x02;
    tx_message.Data[3] = 0x03;
    tx_message.Data[4] = 0x04;
    tx_message.Data[5] = 0x05;
    tx_message.Data[6] = 0x06;
    tx_message.Data[7] = 0x07;
    
    CAN_Transmit(CAN1,&tx_message);
}


void CAN1_TX_IRQHandler(void) //CAN TX
{
    if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
}

void CAN1_RX0_IRQHandler(void)
{   
	  CanRxMsg rx_message;	
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		    CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 
		
		    CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
				CanReceiveMsgProcess(&rx_message);
    }
}



void CAN2_Configuration(void)
{
		CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2); 

    gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 ;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &gpio);

    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = CAN2_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    CAN_DeInit(CAN2);
    CAN_StructInit(&can);

    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;    
    can.CAN_AWUM = DISABLE;    
    can.CAN_NART = DISABLE;    
    can.CAN_RFLM = DISABLE;    
    can.CAN_TXFP = ENABLE;     
    can.CAN_Mode = CAN_Mode_Normal; 
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_5tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 45/(1+9+5)/3=1Mbps
    CAN_Init(CAN2, &can);
    
    can_filter.CAN_FilterNumber=14;
    can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
    can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
    can_filter.CAN_FilterIdHigh=0x0000;
    can_filter.CAN_FilterIdLow=0x0000;
    can_filter.CAN_FilterMaskIdHigh=0x0000;
    can_filter.CAN_FilterMaskIdLow=0x0000;
    can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
    can_filter.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
}


void CAN2_TX_IRQHandler(void) //CAN TX
{
  if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET)    //if transmit mailbox is empty 
  {
	   CAN_ClearITPendingBit(CAN2,CAN_IT_TME);   
  }
}


void CAN2_RX0_IRQHandler(void)
{
    CanRxMsg rx_message;
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
        CAN_Receive(CAN2, CAN_FIFO0, &rx_message);  
       //电机编码器数据处理
				CanReceiveMsgProcess(&rx_message);
    }
}


void CanReceiveMsgProcess(CanRxMsg *rx_message)
{
	
	printf("WELL");
	
				  if((rx_message->IDE == CAN_Id_Standard)&&(rx_message->RTR == CAN_RTR_Data)&&(rx_message->DLC == 8))
        {		
						
						
						//RM3510
						if(rx_message->StdId == 0x201)
            {		
								RM3510_1.lastAngle = RM3510_1.thisAngle; 
                RM3510_1.thisAngle = (rx_message->Data[0]<<8)|(rx_message->Data[1]);
                RM3510_1.thisVelocity = (rx_message->Data[2]<<8)|(rx_message->Data[3]);	
								RM3510_1.thisPosition += (double)GetAngleDiff(RM3510_1.lastAngle,RM3510_1.thisAngle)/8191.0;
								
						}	
						if(rx_message->StdId == 0x202)
            {
								RM3510_2.lastAngle = RM3510_2.thisAngle;
                RM3510_2.thisAngle = (rx_message->Data[0]<<8)|(rx_message->Data[1]);
                RM3510_2.thisVelocity = (rx_message->Data[2]<<8)|(rx_message->Data[3]);	
								RM3510_2.thisPosition += (double)GetAngleDiff(RM3510_2.lastAngle,RM3510_2.thisAngle)/8191.0;
						}	
				    if(rx_message->StdId == 0x203)
            {
								RM3510_3.lastAngle = RM3510_3.thisAngle;
                RM3510_3.thisAngle = (rx_message->Data[0]<<8)|(rx_message->Data[1]);
                RM3510_3.thisVelocity = (rx_message->Data[2]<<8)|(rx_message->Data[3]);	
								RM3510_3.thisPosition += (double)GetAngleDiff(RM3510_3.lastAngle,RM3510_3.thisAngle)/8191.0;
						}	
						if(rx_message->StdId == 0x204)
            {
								RM3510_4.lastAngle = RM3510_4.thisAngle;
                RM3510_4.thisAngle = (rx_message->Data[0]<<8)|(rx_message->Data[1]);
                RM3510_4.thisVelocity = (rx_message->Data[2]<<8)|(rx_message->Data[3]);	
								RM3510_4.thisPosition += (double)GetAngleDiff(RM3510_4.lastAngle,RM3510_4.thisAngle)/8191.0;
						}	
						
        }
}

//RM3510电机
void Cmd_ESC_820R(int16_t current_201,int16_t current_202,int16_t current_203,int16_t current_204)
{
    CanTxMsg tx_message;
    
    tx_message.StdId = 0x200;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = (unsigned char)(current_201 >> 8);
    tx_message.Data[1] = (unsigned char)current_201;
    tx_message.Data[2] = (unsigned char)(current_202 >> 8);
    tx_message.Data[3] = (unsigned char)current_202;
    tx_message.Data[4] = (unsigned char)(current_203 >> 8);
		tx_message.Data[5] = (unsigned char)current_203;
    tx_message.Data[6] = (unsigned char)(current_204 >> 8);
    tx_message.Data[7] = (unsigned char)current_204;
    
    //can2_tx_success_flag = 0;
    CAN_Transmit(CAN2,&tx_message);
    //while(can2_tx_success_flag == 0);
}
//得到角度差
int GetAngleDiff(int16_t lastAngle, int16_t thisAngle)
{
	if(lastAngle-thisAngle<-7000){
		return thisAngle-lastAngle-8191;	
	}
	else if(lastAngle-thisAngle>7000){
		return thisAngle-lastAngle+8191;
	}
	else
		return thisAngle-lastAngle;
}
