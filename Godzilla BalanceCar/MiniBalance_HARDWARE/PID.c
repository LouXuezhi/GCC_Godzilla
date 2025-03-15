#include "stm32f10x.h"  // Device heade

float Balance_Kp;
float Balance_Kd;

float Speed_Kp;
float Speed_Ki;

float Turn_Kp;
float Turn_Kd;

extern uint8_t Flag_Sleep;

extern int Encoder_Left,Encoder_Right;
extern float pitch,row,yaw;
extern float gyrox,gyroy,gyroz;
extern float accx,accy,accz;

//平衡环控制，输入参数为：1. 目标角度 Goal_Angle 2. 真实角度 Real_Angle 3. 真实角速度 Real_gyro_Y
//
int Balance(float Goal_Angle,float Real_Angle,float Real_gyro_Y)
{
	int temp;
	temp=Balance_Kp*(Real_Angle-Goal_Angle)+Balance_Kd*Real_gyro_Y;
	return temp;
}

//平衡环控制，输入参数为：1. 目标角度 Goal_Speed 2. 真实速度 L_Encoder R_Encoder
//
int Speed(int Goal_Speed,int L_Encoder,int R_Encoder)
{
	static int Err_LowOut_Last;
	static int Encoder_Intergal;
	static float LowOut_Parameter;
	int Err,Err_LowOut,temp;
	Err=(L_Encoder+R_Encoder)-Goal_Speed;
	
	Err_LowOut=(1-LowOut_Parameter)*Err+LowOut_Parameter*Err_LowOut_Last;
	Err_LowOut_Last=Err_LowOut;
	
	Encoder_Intergal+=Err_LowOut;
	
	if(Encoder_Intergal>20000)
	{
		Encoder_Intergal=20000;
	}
	if(Encoder_Intergal<-20000)
	{
		Encoder_Intergal=-20000;
	}
	if(Flag_Sleep==1)
	{
		Encoder_Intergal=0;
	}
	temp=Err_LowOut*Speed_Kp+Encoder_Intergal*Speed_Ki;
	return temp;
}


//平衡环控制，输入参数为：1. 目标角度 Goal_Turn 2. 真实角速度 gyro_Z
//

int Turn(float gyro_Z,int Goal_Turn)
{
	int temp;
	temp=Turn_Kp*Goal_Turn+Turn_Kd*gyro_Z;
	return temp;
}