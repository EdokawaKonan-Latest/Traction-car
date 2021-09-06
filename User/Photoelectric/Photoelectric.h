#ifndef _PHOTO_
#define _PHOTO_
#include "stm32f10x.h"
void stop(void);
void PhotoelectricGPIOConfig(void);
void checkPhotoelectric(void);
#define  Three     GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define  One       GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)   
#define  Two       GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)  
#define  Four      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)  
#define  Five      GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)    
#endif  

