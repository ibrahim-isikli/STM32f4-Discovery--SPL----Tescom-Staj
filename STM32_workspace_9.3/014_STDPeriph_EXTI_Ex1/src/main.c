#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_COnfic(void);
void EXTI0_IRQHandler(void);
void delay(uint32_t time);

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

int count=0;

void RCC_Config(void){
	// RCC , clocklarin lerin ayarlanmasi
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
}

void GPIO_Config(void){

 GPIO_InitStruct.GPIO_Mode= GPIO_Mode_OUT;
 GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15);
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
 GPIO_InitStruct.GPIO_Speed =GPIO_Speed_100MHz;
 GPIO_Init(GPIOD,&GPIO_InitStruct);

 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
 GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void EXTI_Config(void){
	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	 EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	 EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	 EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	 EXTI_Init(&EXTI_InitStruct);
}

void NVIC_Config(void){

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =0;
	NVIC_Init(&NVIC_InitStruct);
}

void delay (uint32_t time){
	while(time--);
}

void EXTI0_IRQHandler(void){

	// flag kontrol mekanizmasi EXTI_GetITStatus(EXTI_line0)

	if(EXTI_GetITStatus(EXTI_Line0) != RESET){

				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
					delay(1680000);
				GPIO_ResetBits(GPIOD,GPIO_Pin_13 );
					delay(1680000);
				GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					delay(1680000);
				GPIO_ResetBits(GPIOD,GPIO_Pin_15);
					delay(1680000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	EXTI_Config();
	NVIC_Config();
  while (1)
  {
	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
