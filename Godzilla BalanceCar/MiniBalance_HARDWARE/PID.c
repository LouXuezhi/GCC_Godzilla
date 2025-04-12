#include "stm32f10x.h"  // Device heade


extern float Balance_Kp;
extern float Balance_Kd;

extern float Speed_Kp;
extern float Speed_Ki;

extern float Turn_Kp;
extern float Turn_Kd;
extern float Scaler;
extern uint8_t Flag_Sleep;
extern float Bias;

extern int16_t Encoder_Left,Encoder_Right;
extern float pitch,row,yaw;
extern float gyrox,gyroy,gyroz;
extern float accx,accy,accz;

extern int Speed_Bias;
extern float Turn_Bias;
//平衡环控制，输入参数为：1. 目标角度 Goal_Angle 2. 真实角度 Real_Angle 3. 真实角速度 Real_gyro_Y
//
int Balance(float Goal_Angle,float Real_Angle,float Real_gyro_X)
{
	int temp;
	
	temp=(Balance_Kp*(Real_Angle-Goal_Angle)+Balance_Kd*(Real_gyro_X));
	return temp;
}

//平衡环控制，输入参数为：1. 目标角度 Goal_Speed 2. 真实速度 L_Encoder R_Encoder
//
int Speed(int Goal_Speed,int L_Encoder,int R_Encoder)
{
	static float Err_LowOut_Last;
	static int Encoder_Intergal;
	static float LowOut_Parameter=0.85;
	float Err,Err_LowOut,temp;
	if(Flag_Sleep==1)
	{
		Encoder_Intergal=0;
		return 0;
	}
	Err=Scaler*(L_Encoder+R_Encoder+Bias-2*Speed_Bias/100)-Goal_Speed;
	
	Err_LowOut=(1-LowOut_Parameter)*Err+LowOut_Parameter*Err_LowOut_Last;
	Err_LowOut_Last=Err_LowOut;
	
	Encoder_Intergal+=Err_LowOut;
	
	if(Encoder_Intergal>2000)
	{
		Encoder_Intergal=2000;
	}
	if(Encoder_Intergal<-2000)
	{
		Encoder_Intergal=-2000;
	}
	
	temp=Err_LowOut*Speed_Kp+Encoder_Intergal*Speed_Ki;
	return temp;
}


//平衡环控制，输入参数为：1. 目标角度 Goal_Turn 2. 真实角速度 gyro_Z
//

int Turn(float gyro_Z,int Goal_Turn)
{
	int temp;
	//static float Last_gyro_Z;
	//gyro_Z=Last_gyro_Z*0.9+gyro_Z*0.1;
	//Last_gyro_Z=gyro_Z;
	temp=Turn_Kp*Goal_Turn/100+Turn_Kd*(gyro_Z)/100;//2.7
	return temp;
}
