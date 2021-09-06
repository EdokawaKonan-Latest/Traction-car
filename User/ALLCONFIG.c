#include "ALLCONFIG.h"
#include "pid.h"

PID_Regulator_t moto1;
PID_Regulator_t moto2;
PID_Regulator_t moto3;
PID_Regulator_t moto4;//位置环PID
//PID_Regulator_t moto4;
void ALLCONFIG(void)
{
	PhotoelectricGPIOConfig();//光电初始化
	USART_Config();//串口初始化
	Ecoder_ALL_Config();//编码器初始化
	ALLDUOJIConfig();//舵机初始化
	delay_init();	//延时初始化	
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
