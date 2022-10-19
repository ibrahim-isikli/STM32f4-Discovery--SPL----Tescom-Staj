

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void GPIO_Config(){

	RCC->AHB1ENR=0x00000008;   // clock ebable -> (AHB1ENR BUS) -> port D

	GPIOD-> MODER = 0x55000000;  // 15 14 13 12 pinleri (01 alarak output ayarladik)
	GPIOD->OTYPER = 0x00000000; // tum pinler output push pull (reset state)
	GPIOD->OSPEEDR= 0xFF000000; //  15 14 13 12 pinleri (11 alarak high speed ayarladik)
	GPIOD->PUPDR= 0x00000000; // hepsi 00 no pull aup no pull down


}

void delay(uint32_t time){
	while(time--);
}

int main(void)
{

 GPIO_Config();
  while (1)
  {
	  GPIOD->ODR=0x0000F000;
	  delay(16800000);
	  GPIOD->ODR=0x00000000;
	  delay(16800000);
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){

  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){

  return -1;
}
