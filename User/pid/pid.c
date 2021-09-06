#include  "pid.h"

void PID_Reset_RightWheel(PID_Regulator_t  *pid)
{
	 pid->Set=50.0;    
   pid->Actual=0.0;    
   pid->err=0.0;     
   pid->err_last=0.0;       
   pid->integral=0.0;   
	 pid->kp=8.0;
   pid->ki=0.5; 
	 pid->kd=0.0;
	 pid->output=0.0;
	 pid->integralMax=7200.0;
	 pid->outputMax=719;
}

void PID_Reset_LeftWheel(PID_Regulator_t  *pid)
{
	 pid->Set=20.0;      
   pid->Actual=0.0;    
   pid->err=0.0;     
   pid->err_last=0.0;       
   pid->integral=0.0;   
	 pid->kp=8.0;
   pid->ki=0.5;
   pid->kd=0.0; 
	 pid->output=0.0;
	 pid->integralMax=7200.0;
	 pid->outputMax=719;
}

void PID_Reset_Angle(PID_Regulator_t *pid)
{
	 pid->Set=0.0;      
   pid->Actual=0.0;    
   pid->err=0.0;     
   pid->err_last=0.0;       
   pid->integral=0.0;   
	 pid->kp=0.05;
   pid->ki=0.1;
   pid->kd=0.0;
	 pid->output=0.0;
	 pid->integralMax=7200.0;
	 pid->outputMax=100;
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
