#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdint.h>
#include <stdio.h>

 uint32_t SystemCoreClock;
 uint32_t systemClockInfo;

	// 2) GPIO init structi tanimla
	GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config(void){

	systemClockInfo=SystemCoreClock;

	// 1) RCC -> enable peripheral clock AHB1ENR bus
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	// 3) GPIO Peripheral Registerlari ayarla
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 ;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_NOPULL;

	// 4) GPIO Peripheral Registerlari ayarladik, init etmemiz lazim
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void delay(uint32_t time){
	while(time --); // 8 cycle
}


int main(void)
{
	GPIO_Config();
  while (1)
  {
	  // 5) GPIO config sonra pinleriLOW ve HIGH'a cekmemiz lazim

	  // 168000000/8 = 21000000

	  GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  delay(21000000); // 1 sn bekle
	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	  delay(21000000); // 1 sn bekle

	  // toplamda 2 saniye
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
