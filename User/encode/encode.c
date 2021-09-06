#include "encode.h"
#include "stm32f10x_tim.h"
#include "encode.h"

void TIM_Encoder_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   	

    //时钟使能配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
    //定时器3，4需io口配置	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
    //时基结构体初始化
	TIM_DeInit(TIM4); //定时器时钟使能
	TIM_DeInit(TIM3);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;  //1024线*4==4096一圈。一圈一次中断 //cnt最多也就是1024
	TIM_TimeBaseStructure.TIM_Prescaler	 = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	//TIM4编码器初始化			 
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
   
   //TIM3编码器初始化	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;  
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
   TIM4->CNT =0x7fff;
   TIM3->CNT =0x7fff;
	TIM_Cmd(TIM3, ENABLE); 
	TIM_Cmd(TIM4, ENABLE);    
}

void TIM3_NVIC_Config(void)
{
//溢出中断设置
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
NVIC_InitTypeDef NVIC_InitStructure;
//设置中断组位2
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//设置中断来源  irqtype  stmf10x.h
NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
//使能中断
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//中断优先级设置
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
NVIC_Init(&NVIC_InitStructure);
//设置中断来源  irqtype  stmf10x.h
}

void Ecoder_ALL_Config(void)
{
//TIM3_NVIC_Config();
TIM_Encoder_init();
}








