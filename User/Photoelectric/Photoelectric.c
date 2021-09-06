#include "Photoelectric.h"
#include "pid.h"
#include "ALLCONFIG.h"
extern PID_Regulator_t moto1;
extern PID_Regulator_t moto2;
extern PID_Regulator_t moto3;
void PhotoelectricGPIOConfig()
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
u8 a=0;
u8 b=0;
void checkPhotoelectric()
	{
	if(Three==1&&One==0&&Two==0&&Four==0&&Five==0)
		{
		a=3;
		b=0;
		}
	else if(One==1&&Two==0&&Three==0&&Four==0&&Five==0)//左一遇到黑线 向左转 右边速度增大
		{
		a=1;
		b=1;
		}
	else if(One==0&&Two==1&&Three==0&&Four==0&&Five==0)//左二遇到黑线 向左转 右边速度增大
		{
		a=2;
		}
	else if((One==0&&Two==0&&Three==0&&Four==1&&Five==0))//四遇到黑线 向右边转 左边速度增大
		{
		a=4;
		}
	else if(One==0&&Two==0&&Three==0&&Four==0&&Five==1)//五遇到黑线 向右边转 左边速度增大
		{
		a=5;
		b=1;
		}
	else if(One==0&&Two==0&&Three==0&&Four==0&&Five==0)
		{
      a=a;		
			b=0;
		}
	else if(One==1&&Two==1&&Three==1&&Four==1&&Five==1)
		{
		a=6;
		b=0;	
		}

	switch(a)
		{
		case 3:
		moto3.Actual=-90; //600
		PID_Calc(&moto3);
		printf("%f",moto3.output);
		moto1.Set=abs(moto3.output/40);//27
		moto2.Set=abs(moto3.output/40);//27
		break;
		case 1:
   	PID_Calc(&moto3);
		moto1.Set=-moto3.output/50;
		moto2.Set=moto3.output/50;
		break;
		case 2:
		//if(b==1) moto3.Actual=-40;
		moto3.Actual=moto3.Actual-0.2;
		PID_Calc(&moto3);
		moto1.Set=15-(600.2-moto3.output)/20;
		moto2.Set=15+(600.2-moto3.output)/20;
		b=0;
		break;
		case 4:
		moto3.Actual=moto3.Actual-0.2;
		PID_Calc(&moto3);
		moto1.Set=15+(600.2-moto3.output)/20;
		moto2.Set=15-(600.2-moto3.output)/20;
		b=0;
		break;
		case 5:
	moto3.Actual=moto3.Actual-Five*0.5;
  	PID_Calc(&moto3);
		moto1.Set=moto3.output/22;
		moto2.Set=-moto3.output/22;
		break;
		case 6:
		moto1.Set=0;
		moto2.Set=0;
		b=0;	
	//	printf("TING!!");
		break;
		default:
			a=a;
			break;
		}
	}

