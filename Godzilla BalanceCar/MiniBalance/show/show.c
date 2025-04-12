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
#include "Joled.h"
#include "joled_font.h"
#include "stm32f10x.h" 
#include "show.h"
#include "usart3.h"
// Device header
//float Velocity_Left,Velocity_Right;	//�����ٶ�(mm/s)
extern uint8_t Flag_Mode;
extern int16_t Encoder_Left,Encoder_Right;
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;
extern int Motor_Left,Motor_Right;
extern float Velocity_Left,Velocity_Right;
extern float Distance;
extern u8 Usart3_Receive;
/**************************************************************************
Function: OLED display
Input   : none
Output  : none
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void OLED_InitShow(void)
{
	//Usart_SendByte( USART3, 4);
	OLED_ShowString(1,1,"Gzila BalCar");
	OLED_ShowSignedNum(2,1,Encoder_Left,5);
	OLED_ShowSignedNum(2,7,Encoder_Right,5);
	OLED_ShowSignedNum(3,1,(int)(Angle_Balance*100-60),5);
		OLED_ShowSignedNum(4,1,(int)(Gyro_Turn*100+2700),8);
	
		/*
	//=============��һ����ʾС��ģʽ=======================//	
		     if(Way_Angle==1)	OLED_ShowString(0,0,"DMP");
		else if(Way_Angle==2)	OLED_ShowString(0,0,"Kalman");
		else if(Way_Angle==3)	OLED_ShowString(0,0,"C F");
                   
	       if(Flag_follow==1) OLED_ShowString(70,0,"Follow");
				 else if (Flag_avoid == 1)   OLED_ShowString(70,0,"Avoid ");
 		     else               OLED_ShowString(70,0,"Normal");
		//=============�ڶ�����ʾ�Ƕ�=======================//	
		                      OLED_ShowString(00,10,"Angle");
		if( Angle_Balance<0)	OLED_ShowString(48,10,"-");
		if(Angle_Balance>=0)	OLED_ShowString(48,10,"+");
		                      OLED_ShowNumber(56,10, myabs((int)Angle_Balance),3,12);
	  //=============��������ʾ���ٶ������===============//	
													OLED_ShowString(0,20,"Gyrox");
		if(Gyro_Balance<0)	  OLED_ShowString(42,20,"-");
		if(Gyro_Balance>=0)	  OLED_ShowString(42,20,"+");
		                      OLED_ShowNumber(50,20, myabs((int)Gyro_Balance),4,12);
													
													OLED_ShowNumber(82,20,(u16)Distance,5,12);
			                    OLED_ShowString(114,20,"mm");

		//=============��������ʾ�������PWM�����=======================//		
		                      OLED_ShowString(00,30,"L");
		if(Motor_Left<0)		  OLED_ShowString(16,30,"-"),
													OLED_ShowNumber(26,30,myabs((int)Motor_Left),4,12);
		if(Motor_Left>=0)	    OLED_ShowString(16,30,"+"),
		                      OLED_ShowNumber(26,30,myabs((int)Motor_Left),4,12);
													
		if(Velocity_Left<0)	  OLED_ShowString(60,30,"-");
		if(Velocity_Left>=0)	OLED_ShowString(60,30,"+");
		                      OLED_ShowNumber(68,30,myabs((int)Velocity_Left),4,12);
													OLED_ShowString(96,30,"mm/s");
	
		//=============��������ʾ�ұ�����PWM�����=======================//		
		                      OLED_ShowString(00,40,"R");
		if(Motor_Right<0)		  OLED_ShowString(16,40,"-"),
													OLED_ShowNumber(26,40,myabs((int)Motor_Right),4,12);
		if(Motor_Right>=0)	  OLED_ShowString(16,40,"+"),
		                      OLED_ShowNumber(26,40,myabs((int)Motor_Right),4,12);
													
		if(Velocity_Right<0)	OLED_ShowString(60,40,"-");
		if(Velocity_Right>=0)	OLED_ShowString(60,40,"+");
		                      OLED_ShowNumber(68,40,myabs((int)Velocity_Right),4,12);
													OLED_ShowString(96,40,"mm/s");

		//=============��������ʾ��ѹ��������=======================//
		                      OLED_ShowString(0,50,"V");
													OLED_ShowString(30,50,".");
													OLED_ShowString(64,50,"V");
													OLED_ShowNumber(19,50,Voltage/100,2,12);
													OLED_ShowNumber(42,50,Voltage/10%10,1,12);
													OLED_ShowNumber(50,50,Voltage%10,1,12);
		if(Flag_Stop)         OLED_ShowString(95,50,"OFF");
		if(!Flag_Stop)        OLED_ShowString(95,50,"ON ");
											
		//=============ˢ��=======================//
		OLED_Refresh_Gram();

*/
}




void OLED_ProcessShow(void)
{
	//OLED_Clear();
	OLED_ShowString(1,1,"Mode:");
	OLED_ShowNum(1,6,Flag_Mode,1);
	OLED_ShowSignedNum(2,1,Encoder_Left,5);
	OLED_ShowSignedNum(2,7,Usart3_Receive,5);
	OLED_ShowSignedNum(3,1,(int)(Angle_Balance*100),5);
	OLED_ShowSignedNum(3,7,(int)(Gyro_Balance*100),5);
	OLED_ShowSignedNum(4,1,(int)(Distance*1000),8);
	
}

//Distance;Gyro_Turn
void OLED_SleepShow(void)
{
	OLED_ShowString(1,1,"Sleep Now");
	OLED_ShowString(2,1,"PBut0tON");
}

/**************************************************************************
Function: Send data to APP
Input   : none
Output  : none
�������ܣ���APP��������
��ڲ�������
����  ֵ����
**************************************************************************/
/*
void APP_Show(void)
{    
  static u8 flag;
	int Encoder_Left_Show,Encoder_Right_Show,Voltage_Show;
	Voltage_Show=(Voltage-1000)*2/3;		if(Voltage_Show<0)Voltage_Show=0;if(Voltage_Show>100) Voltage_Show=100;   //�Ե�ѹ���ݽ��д���
	Encoder_Right_Show=Velocity_Right*1.1; if(Encoder_Right_Show<0) Encoder_Right_Show=-Encoder_Right_Show;			  //�Ա��������ݾ������ݴ������ͼ�λ�
	Encoder_Left_Show=Velocity_Left*1.1;  if(Encoder_Left_Show<0) Encoder_Left_Show=-Encoder_Left_Show;
	flag=!flag;
	if(PID_Send==1)			//����PID����,��APP���ν�����ʾ
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)Balance_Kp,(int)Balance_Kd,(int)Velocity_Kp,(int)Velocity_Ki,(int)Turn_Kp,(int)Turn_Kd,0,0,0);//��ӡ��APP����	
		PID_Send=0;	
	}	
   else	if(flag==0)		// ���͵�ص�ѹ���ٶȣ��ǶȵȲ�������APP��ҳ��ʾ
		printf("{A%d:%d:%d:%d}$",(int)Encoder_Left_Show,(int)Encoder_Right_Show,(int)Voltage_Show,(int)Angle_Balance); //��ӡ��APP����
	 else								//����С����̬�ǣ��ڲ��ν�����ʾ
	  printf("{B%d:%d:%d}$",(int)Pitch,(int)Roll,(int)Yaw); //x��y��z��Ƕ� ��APP������ʾ����
																													//�ɰ���ʽ����������ʾ���Σ�������ʾ���
}
*/
/**************************************************************************
Function: Virtual oscilloscope sends data to upper computer
Input   : none
Output  : none
�������ܣ�����ʾ��������λ���������� �ر���ʾ��
��ڲ�������
����  ֵ����
**************************************************************************/
/*
void DataScope(void)
{   
	u8 i;//��������
	float Vol;								//��ѹ����
	unsigned char Send_Count; //������Ҫ���͵����ݸ���
	Vol=(float)Voltage/100;
	DataScope_Get_Channel_Data( Angle_Balance, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
	DataScope_Get_Channel_Data( Distance/10, 2 );         //��ʾ�����������ľ��� ��λ��CM 
	DataScope_Get_Channel_Data( Vol, 3 );                 //��ʾ��ص�ѹ ��λ��V
//		DataScope_Get_Channel_Data( 0 , 4 );   
//		DataScope_Get_Channel_Data(0, 5 ); //����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0 , 6 );//����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
	Send_Count = DataScope_Data_Generate(3);
	for(i = 0 ; i < Send_Count; i++) 
	{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
	}
}
*/
