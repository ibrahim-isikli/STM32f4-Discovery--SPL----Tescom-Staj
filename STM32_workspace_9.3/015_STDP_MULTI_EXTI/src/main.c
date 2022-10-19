#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void RCC_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_Config(void);
void delay (uint32_t time);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);

void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

}

void GPIO_Config(void){

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 );
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_1 |GPIO_Pin_2); // bu sefer A1 ve A2 ye buton baglayalim
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void EXTI_Config(){
	SYSCFG_EXTILineConfig(EXTI_portSourceGPIOA, GPIO_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_portSourceGPIOA, GPIO_PinSource2);
	EXTI_InitStruct.EXTI_Line = (EXTI_Line1 | EXTI_Line2);
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
}

void NVIC_Config(void){

	// 2 tane interrupt var bizim bunlarýn gruop config yapmamiz gerek
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // boylelikle 1. pinin onceligi en yuksek oldu
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
}

void delay(uint32_t time){
	while(time--);
}

void EXTI1_IRQHandler(void){

	// flag kontrolu
	if(EXTI_GetITStatus(EXTI_Line1) != RESET){

		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		delay(1680000);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		delay(16800000);

		// flagi temizle

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}


void EXTI2_IRQHandler(void){

	// flag kontrol
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){

		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(16800000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		delay(16800000);

		EXTI_ClearITPendingBit(EXTI_Line2); // flag clear
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
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
