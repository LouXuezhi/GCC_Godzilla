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
#include "encoder.h"
#include "stm32f10x_gpio.h"

void Encoder_Init_TIM2(void)
{
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//����TIM3��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//��PA6��PA7���ų�ʼ��Ϊ��������
	
	/*ʱ����Ԫ��ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//����ṹ�����
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               //�������ڣ���ARR��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;                //Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM3��ʱ����Ԫ
	
	/*���벶���ʼ��*/
	TIM_ICInitTypeDef TIM_ICInitStructure;							//����ṹ�����
	TIM_ICStructInit(&TIM_ICInitStructure);							//�ṹ���ʼ�������ṹ��û��������ֵ
																	//�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ
																	//����ṹ���ֵ��ȷ��������
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				//ѡ�����ö�ʱ��ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				//ѡ�����ö�ʱ��ͨ��2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	
	/*�������ӿ�����*/
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
																	//���ñ�����ģʽ�Լ���������ͨ���Ƿ���
																	//ע���ʱ������Rising��Falling�Ѿ������������غ��½����ˣ����Ǵ����Ƿ���
																	//�˺������������벶���ʼ��֮����У��������벶������ûḲ�Ǵ˺����Ĳ�������
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM2,0);
	/*TIMʹ��*/
	TIM_Cmd(TIM2, ENABLE);			//ʹ��TIM3����ʱ����ʼ����
}


void Encoder_Init_TIM4(void)
{
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);			//����TIM3��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//��PA6��PA7���ų�ʼ��Ϊ��������
	
	/*ʱ����Ԫ��ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//����ṹ�����
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               //�������ڣ���ARR��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;                //Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM3��ʱ����Ԫ
	
	/*���벶���ʼ��*/
	TIM_ICInitTypeDef TIM_ICInitStructure;							//����ṹ�����
	TIM_ICStructInit(&TIM_ICInitStructure);							//�ṹ���ʼ�������ṹ��û��������ֵ
																	//�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ
																	//����ṹ���ֵ��ȷ��������
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				//ѡ�����ö�ʱ��ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				//ѡ�����ö�ʱ��ͨ��2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	
	/*�������ӿ�����*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
																	//���ñ�����ģʽ�Լ���������ͨ���Ƿ���
																	//ע���ʱ������Rising��Falling�Ѿ������������غ��½����ˣ����Ǵ����Ƿ���
																	//�˺������������벶���ʼ��֮����У��������벶������ûḲ�Ǵ˺����Ĳ�������
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
	/*TIMʹ��*/
	TIM_Cmd(TIM4, ENABLE);			//ʹ��TIM3����ʱ����ʼ����
}



int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM = TIM_GetCounter(TIM2);TIM_SetCounter(TIM2, 0);break;
		 case 4:  Encoder_TIM = TIM_GetCounter(TIM4);TIM_SetCounter(TIM4, 0);break;
		 default: Encoder_TIM=111;
	 }
		return Encoder_TIM;
	
}


void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}


void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}







/**************************************************************************
Function: Initialize TIM2 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/

/*
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  
	TIM_ICStructInit(&TIM_ICInitStructure);	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				//ѡ�����ö�ʱ��ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				//ѡ�����ö�ʱ��ͨ��2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);	
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}
*/
/**************************************************************************
Function: Initialize TIM4 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
/*
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				//ѡ�����ö�ʱ��ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM4, &TIM_ICInitStructure);							//���ṹ���������TIM_ICInit������TIM3�����벶��ͨ��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				//ѡ�����ö�ʱ��ͨ��2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//�����˲������������Թ����źŶ���
	TIM_ICInit(TIM4, &TIM_ICInitStructure);	
	
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}
*/
/**************************************************************************
Function: Read encoder count per unit time
Input   : TIMX��Timer
Output  : none
�������ܣ���λʱ���ȡ����������
��ڲ�����TIMX����ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
/*
int Read_Encoder(u8 TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
*/
/**************************************************************************
Function: TIM4 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
/*
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
*/
/**************************************************************************
Function: TIM2 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
/*
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
*/


