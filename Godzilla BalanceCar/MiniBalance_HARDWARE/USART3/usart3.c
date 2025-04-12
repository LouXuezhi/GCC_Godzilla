/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：5.7
修改时间：2021-04-29

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update：2021-04-29

All rights reserved
***********************************************/
#include "usart3.h"
#include "JOLED.h"
u8 Usart3_Receive;
/**************************************************************************
Function: Usart3 initialization
Input   : bound:Baud rate
Output  : none
函数功能：串口3初始化
入口参数：bound:波特率
返回  值：无
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
              //使能串口1 
	
  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   //USART 初始化设置
  USART_Init(USART1, &USART_InitStructure);     //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	//Led_ShineForEvery2S();
}
*/


void uart3_init(u32 bound)
{  	 
	Led_ShineForEvery2S();
	  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能UGPIOB时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//使能USART3时钟
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
   //USART 初始化设置
	
	
  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure);     //初始化串口3
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口3 


}
/**************************************************************************
Function: Receive interrupt function
Input   : none
Output  : none
函数功能：串口1接收中断
入口参数：无
返回  值：无
**************************************************************************/


void USART1_IRQHandler(void)
{	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收到数据
	{	  
	  static int uart_receive=0;//蓝牙接收相关变量
		//static u8 Flag_PID,i,j,Receive[50];
		//static float Data;
  	uart_receive=USART_ReceiveData(USART1); 
		Usart3_Receive=uart_receive;
		if(uart_receive==0x59)  Flag_Sleep=!Flag_Sleep;  //低速挡（默认值）
		
	  if(uart_receive>0)  //默认使用
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
			}//前
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
			}//刹车
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
  	}
	 											 
} 


/*
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
	{	  
		Led_ShineForEvery2S();
	  static int uart_receive=0;//蓝牙接收相关变量
		//static u8 Flag_PID,i,j,Receive[50];
		//static float Data;
  	uart_receive=USART_ReceiveData(USART3); 
		Usart3_Receive=uart_receive;
		if(uart_receive==0x59)  Flag_Sleep=!Flag_Sleep;  //低速挡（默认值）
		
	  if(uart_receive>0)  //默认使用
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
			}//前
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
			}//刹车
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
  	}
	 											 
} 
*/

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx,ch);

    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
