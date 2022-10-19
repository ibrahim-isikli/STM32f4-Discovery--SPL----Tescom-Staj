
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Clock_Config(void);

void Clock_Config(void){

	/*RCC_CR (clock control register)*/
	RCC->CR |= 0x00090000; // HSEON ve CSSON enable

	/*RCC_PLLCFGR (pll config reg)*/
	RCC->PLLCFGR |= 0x00400000; // PLLSRC -> selected HSE
	// osilator cikisinda 168 MHz almak icin
	RCC->PLLCFGR |= 0x00000004; // PLL_M = 4
	RCC->PLLCFGR |= 0x00005A00; // PLL_N = 168(hex)
	RCC->PLLCFGR |= 0x00000000; // PLL_P = 2

	/*RCC_CFGR (clock config reg)*/
	RCC->CFGR |= 0x00000000; // hpre AHB prescaler (1)
	RCC->CFGR |= 0x00008000; // ppre2 (2)
	RCC->CFGR |= 0x00001400; // ppre1 (4)

	/*RCC_CIR (clock ýnterrupt reg)*/
	RCC->CIR |= 0X00880000; // HSERDY ve CSS flag clear

	//peripheral clock
	RCC->AHB1ENR |= 0x00000008; // port D enable
			GPIOD-> MODER = 0x55000000;  // 15 14 13 12 pinleri (01 alarak output ayarladik)
	    	GPIOD->OTYPER = 0x00000000; // tum pinler output push pull (reset state)
	    	GPIOD->OSPEEDR = 0xFF000000; //  15 14 13 12 pinleri (11 alarak high speed ayarladik)
	    	GPIOD->PUPDR = 0x00000000; // hepsi 00 no pull aup no pull down
}

int main(void)
{
	Clock_Config();
  while (1)
  {

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
