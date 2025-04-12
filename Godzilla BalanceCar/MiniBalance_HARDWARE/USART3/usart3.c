/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��5.7
�޸�ʱ�䣺2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update��2021-04-29

All rights reserved
***********************************************/
#include "usart3.h"
#include "JOLED.h"
u8 Usart3_Receive;
/**************************************************************************
Function: Usart3 initialization
Input   : bound:Baud rate
Output  : none
�������ܣ�����3��ʼ��
��ڲ�����bound:������
����  ֵ����
**************************************************************************/
extern uint8_t Flag_Sleep;
extern uint8_t Flag_Mode;
extern float Target_Speed;
extern float Bias;
extern int Speed_Bias;
extern int BlueTooth_Mode;
/*
void uart3_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
              //ʹ�ܴ���1 
	
  //Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   //USART ��ʼ������
  USART_Init(USART1, &USART_InitStructure);     //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	//Led_ShineForEvery2S();
}
*/


void uart3_init(u32 bound)
{  	 
	Led_ShineForEvery2S();
	  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��UGPIOBʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART3ʱ��
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
   //USART ��ʼ������
	
	
  //Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure);     //��ʼ������3
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���3 


}
/**************************************************************************
Function: Receive interrupt function
Input   : none
Output  : none
�������ܣ�����1�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/


void USART1_IRQHandler(void)
{	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //���յ�����
	{	  
	  static int uart_receive=0;//����������ر���
		//static u8 Flag_PID,i,j,Receive[50];
		//static float Data;
  	uart_receive=USART_ReceiveData(USART1); 
		Usart3_Receive=uart_receive;
		if(uart_receive==0x59)  Flag_Sleep=!Flag_Sleep;  //���ٵ���Ĭ��ֵ��
		
	  if(uart_receive>0)  //Ĭ��ʹ��
    {			
			if(uart_receive==0x5A)	    
			{
				//Flag_Mode=1;
				
				//Bias=2;
				//Speed_Bias=100;
				//Target_Speed=1;
				BlueTooth_Mode=11;
				Led_ShineForEvery2S();
			}
			else if(uart_receive==0x41)
			
				//Flag_Mode=1;
				//Bias=4;
			//Speed_Bias=200;
			Target_Speed=2;
			BlueTooth_Mode=12;
			}//ǰ
			else if(uart_receive==0x45)
			{
				//Flag_Mode=1;
				//Bias=6;
				//Speed_Bias=300;
				//Target_Speed=10;
				BlueTooth_Mode=13;
			}
			else if(uart_receive==0x42)	
			{
				//Flag_Mode=2;
				//Bias=2;
				//Speed_Bias=100;
				//Target_Speed=1;
				BlueTooth_Mode=21;
			}
			else if(uart_receive==0x46)	    
			{
				//Flag_Mode=2;
				//Bias=4;
				//Speed_Bias=200;
				//Target_Speed=2;
				BlueTooth_Mode=22;
			}
			else if(uart_receive==0x48)
			{
				//Flag_Mode=2;
				//Bias=6;
				//Speed_Bias=300;
				//Target_Speed=3;
				BlueTooth_Mode=23;
			}//ɲ��
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
  	}
	 											 
} 


/*
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
	{	  
		Led_ShineForEvery2S();
	  static int uart_receive=0;//����������ر���
		//static u8 Flag_PID,i,j,Receive[50];
		//static float Data;
  	uart_receive=USART_ReceiveData(USART3); 
		Usart3_Receive=uart_receive;
		if(uart_receive==0x59)  Flag_Sleep=!Flag_Sleep;  //���ٵ���Ĭ��ֵ��
		
	  if(uart_receive>0)  //Ĭ��ʹ��
    {			
			if(uart_receive==0x5A)	    
			{
				Flag_Mode=1;
				
				//Bias=2;
				//Speed_Bias=100;
				Led_ShineForEvery2S();
			}
			else if(uart_receive==0x41)
			
				Flag_Mode=1;
				//Bias=4;
			//Speed_Bias=200;
			}//ǰ
			else if(uart_receive==0x45)
			{
				Flag_Mode=1;
				//Bias=6;
				//Speed_Bias=300;
			}
			else if(uart_receive==0x42)	
			{
				Flag_Mode=2;
				//Bias=2;
				Speed_Bias=100;
			}
			else if(uart_receive==0x46)	    
			{
				Flag_Mode=2;
				//Bias=4;
				Speed_Bias=200;
			}
			else if(uart_receive==0x48)
			{
				Flag_Mode=2;
				//Bias=6;
				Speed_Bias=300;
			}//ɲ��
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
  	}
	 											 
} 
*/

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
    /* ����һ���ֽ����ݵ�USART */
    USART_SendData(pUSARTx,ch);

    /* �ȴ��������ݼĴ���Ϊ�� */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
