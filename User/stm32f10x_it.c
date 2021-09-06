/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI

  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "pid.h"
#include "Photoelectric.h"
#include "Location.h"
extern volatile uint32_t time;//计时变量//计时变量

extern volatile uint32_t time1;

extern PID_Regulator_t moto1;
extern PID_Regulator_t moto2;
extern PID_Regulator_t moto3;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
	{
	}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
	{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
		{
		}
	}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
	{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
		{
		}
	}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
	{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
		{
		}
	}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
	{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
		{
		}
	}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
	{
	}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
	{
	}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
	{
	}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
	{
	}

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
	{
	uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
		{
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
		USART_SendData(DEBUG_USARTx,ucTemp);
		}
	}


void  TIM1_UP_IRQHandler(void)//高级定时器
	{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
		{
		
	  PID_Calc(&moto3);
		int cnt,cnt2;
		cnt=0x7fff-TIM3->CNT;  //当前减初始
		TIM3->CNT=0x7fff;
		moto1.Actual=cnt;			
		PID_Calc(&moto1);			
		cnt2=0x7fff-TIM4->CNT;  //当前减初始
		TIM4->CNT=0x7fff;
		moto2.Actual=cnt2;
		PID_Calc(&moto2);
  //  printf("R==%d\r\n",cnt2);		
  //checkPhotoelectric();
    check_cnt(cnt);
		if(moto1.output>=0)
			{
			TIM_SetCompare1(TIM2,moto1.output);//左正
			TIM_SetCompare4(TIM2,0);//左负
			}
		else
			{
			TIM_SetCompare1(TIM2,0);//左正
			TIM_SetCompare4(TIM2,abs(moto1.output));//左负
			}

		if(moto2.output>=0)
			{
			TIM_SetCompare3(TIM2,moto2.output);//右正
			TIM_SetCompare2(TIM2,0);//右负
			}
	  else {
			TIM_SetCompare3(TIM2,0);//右正
			TIM_SetCompare2(TIM2,abs(moto2.output));//右负
			}
		}
	TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);
	}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
