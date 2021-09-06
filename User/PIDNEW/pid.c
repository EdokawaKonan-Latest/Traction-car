#include  "pid.h"

void PID_Reset_RightWheel(PID_Regulator_t *pid)
	{
	pid->Set=0;
	pid->Actual=0.0; 
	pid->err=0.0;
	pid->err_last=0.0;
	pid->integral=0.0;
	pid->kp=140;
	pid->ki=0.45; 
	pid->kd=10;
	pid->output=0.0;
	pid->integralMax=600;//定时器TIM2进行控制最大值
	pid->outputMax=600;
	}
void PID_Reset_LeftWheel(PID_Regulator_t  *pid)
	{       
	pid->Set=0;
	pid->Actual=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->integral=0.0;                                                                ;
	pid->kp=140.0;
	pid->ki=0.45;          
	pid->kd=10;
	pid->output=0.0;
	pid->integralMax=600;//定时器TIM2进行控制最大值
	pid->outputMax=600;
	}
	void PID_Reset_Photoelectric(PID_Regulator_t *pid)//光电闭环
	{
	pid->Set=0.0;
	pid->Actual=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->integral=0.0;
	pid->kp=1;
	pid->ki=0.468;
	pid->kd=0.0;
	pid->output=0.0;
	pid->integralMax=1000;//定时器TIM2进行控制最大值
	pid->outputMax=1000;
	}
	
		void PID_Reset_Location(PID_Regulator_t *pid)//位置环
	{
	pid->Set=3000;
	pid->Actual=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->integral=0.0;
	pid->kp=0.1;
	pid->ki=0;
	pid->kd=0.0;
	pid->output=0.0;
	pid->integralMax=2000;//定时器TIM2进行控制最大值
	pid->outputMax=2000;
	}
	 void PID_Reset_Angle(PID_Regulator_t *pid)//角度环
	 {
	pid->Set=3000;
	pid->Actual=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->integral=0.0;
	pid->kp=0.1;
	pid->ki=0;
	pid->kd=0.0;
	pid->output=0.0;
	pid->integralMax=2000;//定时器TIM2进行控制最大值
	pid->outputMax=2000;	 
	 }

void Change_Photoelectric_Actual(PID_Regulator_t  *pid,float actual)//遇到不同光电改变初始actual值
	{
	pid->Actual=actual;
	}


void PID_Calc(PID_Regulator_t *pid)
	{
	pid->err=pid->Set-pid->Actual;
	pid->integral+=pid->err;
	pid->output=pid->kp*pid->err+pid->ki*pid->integral+pid->kd*(pid->err-pid->err_last);
	pid->err_last=pid->err;

	//限幅
	if(abs(pid->output) > pid->outputMax)
		{
		if(pid->output>0)
			{
			pid->output=pid->outputMax;
			}
		else
			{
			pid->output=-pid->outputMax;
			}
		}
	//限积分量
	if(abs(pid->integral) > pid->integralMax)
		{
		if(pid->integral>0)
			{
			pid->integral=pid->integralMax;
			}
		else
			{
			pid->integral=-pid->integralMax;
			}
		}
	}

int Incremental_PI (PID_Regulator_t *pid)
	{
	static int Pwm;
	pid->err=pid->Actual-pid->Set;
	Pwm+=pid->kp*(pid->err-pid->err_last)+pid->ki*pid->err;
	pid->err_last=pid->err;
	return Pwm;
	}
