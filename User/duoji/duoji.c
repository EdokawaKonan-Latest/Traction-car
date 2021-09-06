#include "duoji.h"
#include "stm32f10x_tim.h"

void DUOJI_PWM_Config()
	{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 开启定时器时钟,即内部时钟CK_INT=72M
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2,ENABLE);

	/*--------------------时基结构体初始化-------------------------*/

	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period= 999;
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// 初始化定时器
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/

	// 配置为PWM模式2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	// 设置占空比大小
	TIM_OCInitStructure.TIM_Pulse =0;

	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	// 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;



	//电机1高
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//通道一初始化  PA0
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//通道三输出使能 PA0

	//电机1低
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//通道二初始化  PA1
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//通道二使能    使能预装载寄存器

	//电机二高
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//通道三初始化  PA2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//通道三输出使能 PA2

	//电机二低
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//通道三初始化  PA3
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//通道三输出使能 PA2

	// 使能计数器
	TIM_Cmd(TIM2, ENABLE);

	}

//TIM2所需io口配置
void DUOJI_IO_Congfig()
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	// TIM2输出比较通道 GPIO A0123初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
void ALLDUOJIConfig()
	{
	DUOJI_IO_Congfig();
	DUOJI_PWM_Config();
	}
