#ifndef _PID_H
#define _PID_H
#define abs(x) ((x)>0? (x):(-(x)))
#include "stm32f10x.h"
typedef struct
{
	float Set;           //定义设定值 
	float Actual;        //定义实际值
	float err;           //定义偏差值 
  float err_last;      //定义上一个偏差值
	float kp;						 //P
	float ki;						 //I
	float kd;						 //D
	float integral;      //定义积分值 
	float output;				 //输出值
	float integralMax;   //积分上限
	float outputMax;		 //输出上限
	float errMax;        //偏差上限
	float errMin;        //偏差下限	
}
PID_Regulator_t;


void PID_Reset_Right(PID_Regulator_t  *pid);
void PID_Reset_Left(PID_Regulator_t *pid);
void PID_Reset_Angle(PID_Regulator_t *pid);
void PID_Calc(PID_Regulator_t *pid);
int Incremental_PI (PID_Regulator_t *pid);

#endif

