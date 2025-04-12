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
#include "stm32f10x.h"
#include "sys.h"
#include "JOLED.h"

u8 Way_Angle=2;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
//u8 Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_velocity=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;//���ֹͣ��־λ����ʾ��־λ  Ĭ��ֹͣ ��ʾ��
u8 Flag_BlueTeethMode;
u8 ShowTime=0;
u8 ShowLastTime=0;
int Motor_Left,Motor_Right;                 //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //�¶ȱ���
//int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
//u32 Distance;                               //���������
u8 delay_50,delay_flag,PID_Send; 						//��ʱ�͵�����ر���
//u8 Flag_follow=0,Flag_avoid=0;							//���������桢���������ϱ�־λ
float Acceleration_Z;                       //Z����ٶȼ�  

//С������������
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
//���Ʊ���
uint8_t Flag_Sleep=1;
uint8_t Flag_Mode=0;
float Target_Speed=0;
uint16_t Target_Turn=0;
uint16_t Turn_Right=0;
uint16_t Turn_Left=0;
float Distance=0;
//��������
float Goal_Balance_Angle=-0.6;
int count =0;
float Turn_Bias_Small;
int BlueTooth_Mode;
int main(void)
{ 
	MY_NVIC_PriorityGroupConfig(2);	//�����жϷ���
	delay_init();	    	            //��ʱ������ʼ��	
	JTAG_Set(JTAG_SWD_DISABLE);     //�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init(); 	//��ʼ���� LED ���ӵ�Ӳ���ӿ�
	Led_ShineForEvery2S();
	//KEY_Init();   
	//������ʼ��
	//MiniBalance_Motor_Init();
	MiniBalance_PWM_Init(7199,0);   //��ʼ��PWM 10KHZ����Ӳ���ӿڣ������������
	//uart_init(115200);	            //����1��ʼ��
	uart3_init(9600);             	//����3��ʼ������������ģ��
	Encoder_Init_TIM2();            //�������ӿ�
	Encoder_Init_TIM4(); 	//��ʼ��������4
	//Led_ShineForEvery2S();
	//Adc_Init(); 	//adc��ʼ��
	//Led_ShineForEvery2S();
	IIC_Init(); 	//IIC*��ʼ��
	//Led_ShineForEvery2S();
	OLED_Init();                    //OLED��ʼ��	    
	MPU6050_initialize(); 	//MPU6050��ʼ��
	//Led_ShineForEvery2S();	
	DMP_Init();//��ʼ��DMP 
	//Led_ShineForEvery2S();
	button0_init();	
	button1_init();
	button2_init();
	//TIM3_Cap_Init(0XFFFF,72-1);	    //��������ʼ��
	//Led_ShineForEvery2S();
	MiniBalance_EXTI_Init();	//MPU6050 5ms��ʱ�жϳ�ʼ������ʡ��ʱ����Դ������cpu����
	
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
		if(Flag_Show==0)          		//ʹ��MiniBalance APP��OLED��ʾ��
		{
			 APP_Show();								//�������ݸ�APP
			 oled_show();          			//��ʾ����
		}
		else                      		//ʹ��MiniBalance��λ�� ��λ��ʹ�õ�ʱ����Ҫ�ϸ��ʱ�򣬹ʴ�ʱ�ر�app��ز��ֺ�OLED��ʾ��
		{
			 //DataScope();          			//����MiniBalance��λ��
		}	
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);
*/		//ʾ������Ҫ50ms	�߾�����ʱ��delay����������Ҫ�󣬹�ʹ��MPU6050�ж��ṩ50ms��ʱ
	
		
}

