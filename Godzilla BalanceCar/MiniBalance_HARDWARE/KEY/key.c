#include "key.h"
#include "stm32f10x.h" 
#include "delay.h"// Device header


uint8_t Key_GetNum(void)//获取按键输出
{
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
	{
		delay_ms(20);//延迟减小抖动影响
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);//等待按键恢复，按下为低电平，恢复为高电平
		delay_ms(20);
		KeyNum = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0);
		delay_ms(20);
		KeyNum = 2;
	}
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0);
		delay_ms(20);
		KeyNum = 3;
	}
	return KeyNum;
}


/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
函数功能：按键初始化
入口参数：无
返回  值：无 
**************************************************************************/
/*void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
} */
/**************************************************************************
Function: Key scan
Input   : Double click the waiting time
Output  : 0：No action；1：click；2：Double click
函数功能：按键扫描
入口参数：双击等待时间
返回  值：按键状态 0：无动作 1：单击 2：双击 
**************************************************************************/
/*
u8 click_N_Double (u8 time)
{
	static	u8 flag_key,count_key,double_key;	
	static	u16 count_single,Forever_count;
	if(KEY==0)  Forever_count++;   //长按标志位未置1
	else        Forever_count=0;
	if(0==KEY&&0==flag_key)		flag_key=1;	//第一次按下
	if(0==count_key)
	{
			if(flag_key==1) 
			{
				double_key++;
				count_key=1;			//标记按下一次
			}
			if(double_key==2) 
			{										//按下两次
				double_key=0;
				count_single=0;
				return 2;					//双击执行的指令
			}
	}
	if(1==KEY)			flag_key=0,count_key=0;
	
	if(1==double_key)
	{
		count_single++;
		if(count_single>time&&Forever_count<time)
		{
			double_key=0;
			count_single=0;	//超时不标记为双击
		return 1;//单击执行的指令
		}
		if(Forever_count>time)
		{
			double_key=0;
			count_single=0;	
		}
	}	
	return 0;
}
*/
/**************************************************************************
Function: Key scan
Input   : none
Output  : 0：No action；1：click；
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：单击 
**************************************************************************/
/*
u8 click(void)
{
	static u8 flag_key=1;//按键按松开标志
	if(flag_key&&KEY==0) //检测到按键按下
	{
		flag_key=0;
		return 1;	//按键按下
	}
	else if(1==KEY)			flag_key=1;
	return 0;//无按键按下
}
*/
/**************************************************************************
Function: Long press detection
Input   : none
Output  : 0：No action；1：Long press for 2 seconds；
函数功能：长按检测
入口参数：无
返回  值：按键状态 0：无动作 1：长按2s
**************************************************************************/
/*
u8 Long_Press(void)
{
		static u16 Long_Press_count,Long_Press;
	  if(Long_Press==0&&KEY==0)  Long_Press_count++;   //长按标志位未置1
    else                       Long_Press_count=0; 
		if(Long_Press_count>200)		//10ms扫描一次
	  {
			Long_Press=1;	
			Long_Press_count=0;
			return 1;
		}				
		if(Long_Press==1)     //长按标志位置1
		{
			Long_Press=0;
		}
		return 0;
}
*/
