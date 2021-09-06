#include "basetime.h"

static void BASIC_TIM_NVIC_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
//�����ж���λ0
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//ʹ���ж�
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//�ж����ȼ�����
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
NVIC_Init(&NVIC_InitStructure);
//�����ж���Դ  irqtype  stmf10x.h
NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
NVIC_Init(&NVIC_InitStructure);
}

static void TimBasicConfig()
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//������ʱ��ʱ�ӣ����ڲ�ʱ��ck_init=72M
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);
//�Զ���װ�ؼĴ�����ֵ�����TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
TIM_TimeBaseStructure.TIM_Period=2999;//2ms
//ʱ��Ԥ��Ƶϵ��
TIM_TimeBaseStructure.TIM_Prescaler=71;
//ʱ�ӷ�Ƶ����
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//����������ģʽ
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
//�ظ���������ֵ
TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
//��ʼ����ʱ��
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
//����������жϱ�־λ
TIM_ClearFlag( TIM1, TIM_FLAG_Update);
//�����������ж�
//�жϿ����������жϱ�־λλ1��ֻ�Ǵ��������жϣ�������ʱ�����������
TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
//ʹ�ܼ�����
TIM_Cmd(TIM1,ENABLE);
}

void BASIC_TIM_Init(void)
{
 TimBasicConfig();
 
  BASIC_TIM_NVIC_Config();
}



