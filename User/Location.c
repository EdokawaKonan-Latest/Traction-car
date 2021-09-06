#include "Location.h"
extern  PID_Regulator_t moto4;
extern  PID_Regulator_t moto1;
void check_cnt(int cnt)
{
	moto4.Actual+=cnt;
  PID_Calc(&moto4);
	moto1.Set=moto4.output;	   
	printf("%d\r\n",(int)(moto4.Actual));
}

