#ifndef __PID_H
#define __PID_H

int Balance(float Goal_Angle,float Real_Angle,float Real_gyro_Y);
int Speed(int Goal_Speed,int L_Encoder,int R_Encoder);
int Turn(float gyro_Z,int Goal_Turn);
	
#endif
