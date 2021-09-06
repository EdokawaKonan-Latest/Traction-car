#include "ALLCONFIG.h"
#include "pid.h"

PID_Regulator_t moto1;
PID_Regulator_t moto2;
PID_Regulator_t moto3;
PID_Regulator_t moto4;//λ�û�PID
//PID_Regulator_t moto4;
void ALLCONFIG(void)
{
	PhotoelectricGPIOConfig();//����ʼ��
	USART_Config();//���ڳ�ʼ��
	Ecoder_ALL_Config();//��������ʼ��
	ALLDUOJIConfig();//�����ʼ��
	delay_init();	//��ʱ��ʼ��	
  PID_Reset_RightWheel(&moto2);
  PID_Reset_LeftWheel(&moto1); 
  PID_Reset_Photoelectric(&moto3);
	PID_Reset_Location(&moto4);

}
void Delay_s(u16 s)  
{
	int i;
	for (i = 0; i < s; i++)
		delay_ms(1000);
}
