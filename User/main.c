#include "ALLCONFIG.h"
#include "pid.h"
extern PID_Regulator_t moto1;
extern int circle_count;
extern PID_Regulator_t moto3;
volatile uint32_t time1 = 0;//��ʱ����
int main(void)
	{
	
	ALLCONFIG();//��������
	BASIC_TIM_Init();//������ʱ����ʼ�� 
				
		while (1)
		{
		}

	}
