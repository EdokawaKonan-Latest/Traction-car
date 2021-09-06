#include "basetime.h"

static void BASIC_TIM_NVIC_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
//设置中断组位0
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//使能中断
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//中断优先级设置
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
NVIC_Init(&NVIC_InitStructure);
//设置中断来源  irqtype  stmf10x.h
NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
NVIC_Init(&NVIC_InitStructure);
}

static void TimBasicConfig()
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//开启定时器时钟，即内部时钟ck_init=72M
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);
//自动重装载寄存器的值，类继TIM_Period+1个频率后产生一个更新或者中断
TIM_TimeBaseStructure.TIM_Period=2999;//2ms
//时钟预分频系数
TIM_TimeBaseStructure.TIM_Prescaler=71;
//时钟分频因子
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//计数器计数模式
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
//重复计数器的值
TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
//初始化定时器
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
//清除计数器中断标志位
TIM_ClearFlag( TIM1, TIM_FLAG_Update);
//开启计数器中断
//中断开启不代表中断标志位位1，只是代表开启了中断，启动的时候可以启动。
TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
//使能计数器
TIM_Cmd(TIM1,ENABLE);
}

void BASIC_TIM_Init(void)
{
 TimBasicConfig();
 
  BASIC_TIM_NVIC_Config();
}



