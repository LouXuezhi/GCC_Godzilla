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
#include "stm32f10x.h"
#include "sys.h"
#include "JOLED.h"

u8 Way_Angle=2;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
//u8 Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_velocity=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;//电机停止标志位和显示标志位  默认停止 显示打开
u8 Flag_BlueTeethMode;
u8 ShowTime=0;
u8 ShowLastTime=0;
int Motor_Left,Motor_Right;                 //电机PWM变量 应是Motor的 向Moto致敬	
int Temperature;                            //温度变量
//int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
//u32 Distance;                               //超声波测距
u8 delay_50,delay_flag,PID_Send; 						//延时和调参相关变量
//u8 Flag_follow=0,Flag_avoid=0;							//超声波跟随、超声波壁障标志位
float Acceleration_Z;                       //Z轴加速度计  

//小车传感器变量
int16_t Encoder_Left,Encoder_Right;
float Velocity_Left,Velocity_Right;
float pitch,row,yaw;
float gyrox,gyroy,gyroz;
float accx,accy,accz;

float Balance_Kp;
float Balance_Kd;//2.5*0.5;//2.5*0.51;

//float Balance_Kp=0;//500
//float Balance_Kd=0;
float Speed_Kp;//
float Speed_Ki;//


float Turn_Kp;
float Turn_Kd;

int Speed_Bias;
float Turn_Bias;
float Scaler;
float Bias;
//控制变量
uint8_t Flag_Sleep=1;
uint8_t Flag_Mode=0;
float Target_Speed=0;
uint16_t Target_Turn=0;
uint16_t Turn_Right=0;
uint16_t Turn_Left=0;
float Distance=0;
//常数变量
float Goal_Balance_Angle=-0.6;
int count =0;
float Turn_Bias_Small;
int BlueTooth_Mode;
int main(void)
{ 
	MY_NVIC_PriorityGroupConfig(2);	//设置中断分组
	delay_init();	    	            //延时函数初始化	
	JTAG_Set(JTAG_SWD_DISABLE);     //关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //打开SWD接口 可以利用主板的SWD接口调试
	LED_Init(); 	//初始化与 LED 连接的硬件接口
	Led_ShineForEvery2S();
	//KEY_Init();   
	//按键初始化
	//MiniBalance_Motor_Init();
	MiniBalance_PWM_Init(7199,0);   //初始化PWM 10KHZ与电机硬件接口，用于驱动电机
	//uart_init(115200);	            //串口1初始化
	uart3_init(9600);             	//串口3初始化，用于蓝牙模块
	Encoder_Init_TIM2();            //编码器接口
	Encoder_Init_TIM4(); 	//初始化编码器4
	//Led_ShineForEvery2S();
	//Adc_Init(); 	//adc初始化
	//Led_ShineForEvery2S();
	IIC_Init(); 	//IIC*初始化
	//Led_ShineForEvery2S();
	OLED_Init();                    //OLED初始化	    
	MPU6050_initialize(); 	//MPU6050初始化
	//Led_ShineForEvery2S();	
	DMP_Init();//初始化DMP 
	//Led_ShineForEvery2S();
	button0_init();	
	button1_init();
	button2_init();
	//TIM3_Cap_Init(0XFFFF,72-1);	    //超声波初始化
	//Led_ShineForEvery2S();
	MiniBalance_EXTI_Init();	//MPU6050 5ms定时中断初始化，节省定时器资源，减少cpu负担
	
	//Led_ShineForEvery2S();
	
	while(1)
	{
		//GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_14);
		//GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_15);
		if (Flag_Mode==0)
		{
			ShowTime=0;
			ShowLastTime=0;
			if(ShowLastTime!=ShowTime)
			{
				OLED_Clear();
			}
			OLED_InitShow();
			
			ShowLastTime=ShowTime;
		}
		if (Flag_Sleep==0&&Flag_Mode==1)
		{
			ShowTime=1;
			if (ShowLastTime!=ShowTime)
			{
				OLED_Clear();
			}
			OLED_ProcessShow();
			ShowLastTime=ShowTime;
		}
		if (Flag_Sleep==0&&Flag_Mode==2)
		{
			ShowTime=2;
			if (ShowLastTime!=ShowTime)
			{
				OLED_Clear();
			}
			
			OLED_ProcessShow();
			ShowLastTime=ShowTime;
		}
		


	}			
		/*
		if(Flag_Show==0)          		//使用MiniBalance APP和OLED显示屏
		{
			 APP_Show();								//发送数据给APP
			 oled_show();          			//显示屏打开
		}
		else                      		//使用MiniBalance上位机 上位机使用的时候需要严格的时序，故此时关闭app监控部分和OLED显示屏
		{
			 //DataScope();          			//开启MiniBalance上位机
		}	
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);
*/		//示波器需要50ms	高精度延时，delay函数不满足要求，故使用MPU6050中断提供50ms延时
	
		
}

