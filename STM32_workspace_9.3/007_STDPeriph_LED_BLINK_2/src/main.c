
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdint.h>
#include <stdio.h>

extern uint32_t SystemCoreClock;
volatile uint32_t systemClockInfo;

	// 2) GPIO init structi tanimla
	GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config(void){

	systemClockInfo=SystemCoreClock;

	// 1) RCC -> enable peripheral clock AHB1ENR bus
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	// 3) GPIO Peripheral Registerlari ayarla
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_NOPULL;

	// 4) GPIO Peripheral Registerlari ayarladik, init etmemiz lazim
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void delay(uint32_t time){
	while(time --);
}


int main(void)
{
	GPIO_Config();
  while (1)
  {
	  // 5) GPIO config sonra pinleriLOW ve HIGH'a cekmemiz lazim

	  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  delay(168000000); // 1 sn bekle
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  delay(168000000); // 1 sn bekle
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
