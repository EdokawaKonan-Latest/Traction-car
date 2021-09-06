#include "ALLCONFIG.h"
#include "pid.h"
extern PID_Regulator_t moto1;
extern int circle_count;
extern PID_Regulator_t moto3;
volatile uint32_t time1 = 0;//计时变量
int main(void)
	{
	
	ALLCONFIG();//所有配置
	BASIC_TIM_Init();//基本定时器初始化 
				
		while (1)
		{
		}

	}
