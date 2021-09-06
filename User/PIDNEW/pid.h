#ifndef _PID_H
#define _PID_H
#define abs(x) ((x)>0? (x):(-(x)))
#include "stm32f10x.h"
typedef struct
{
	float Set;           //�����趨ֵ 
	float Actual;        //����ʵ��ֵ
	float err;           //����ƫ��ֵ 
  float err_last;      //������һ��ƫ��ֵ
	float kp;						 //P
	float ki;						 //I
	float kd;						 //D
	float integral;      //�������ֵ 
	float output;				 //���ֵ
	float integralMax;   //��������
	float outputMax;		 //�������
	float errMax;        //ƫ������
	float errMin;        //ƫ������	
}
PID_Regulator_t;
void PID_Reset_LeftWheel(PID_Regulator_t  *pid);
void PID_Reset_RightWheel(PID_Regulator_t *pid);
void PID_Reset_Angle(PID_Regulator_t *pid);
void PID_Calc(PID_Regulator_t *pid);
int Incremental_PI (PID_Regulator_t *pid);
void Change_RightWheelSet(PID_Regulator_t  *pid,float Speed);
void Change_LeftWheelSet(PID_Regulator_t  *pid,float Speed);
void PID_Reset_Photoelectric(PID_Regulator_t *pid);
void Change_Photoelectric_Actual(PID_Regulator_t  *pid,float actual);
void PID_Reset_Location(PID_Regulator_t *pid);
#endif

