#include "duoji.h"
#include "stm32f10x_tim.h"

void DUOJI_PWM_Config()
	{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2,ENABLE);

	/*--------------------ʱ���ṹ���ʼ��-------------------------*/

	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period= 999;
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/

	// ����ΪPWMģʽ2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	// ����ռ�ձȴ�С
	TIM_OCInitStructure.TIM_Pulse =0;

	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	// ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;



	//���1��
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//ͨ��һ��ʼ��  PA0
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//ͨ�������ʹ�� PA0

	//���1��
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//ͨ������ʼ��  PA1
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//ͨ����ʹ��    ʹ��Ԥװ�ؼĴ���

	//�������
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//ͨ������ʼ��  PA2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//ͨ�������ʹ�� PA2

	//�������
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//ͨ������ʼ��  PA3
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//ͨ�������ʹ�� PA2

	// ʹ�ܼ�����
	TIM_Cmd(TIM2, ENABLE);

	}

//TIM2����io������
void DUOJI_IO_Congfig()
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	// TIM2����Ƚ�ͨ�� GPIO A0123��ʼ��
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
