#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
int i=0;

void delay(uint32_t time){
	while(time--);
}

void RCC_Config(){

			/*RCC_CR (clock control register)*/
			RCC->CR |= (1<<16); 	// HSEON enable

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
}


	void DAC1_Config(){
		RCC->AHB1ENR |= 0x00000001;
		RCC->APB1ENR |= 0x20000000;
		DAC->CR |= 0x00000001; // dac channel 1 enable
		DAC->SWTRIGR |= 0x00000000; // dac channel 1 software trigger disable
		DAC->DHR12R1 |= 0x00000000; // dac channel 1 12-bit right aligned olarak ayarladik
		// a portunun 4. pini


	}


int main(void)
{
	RCC_Config();
	DAC1_Config();

  while (1)
  {
	 for (i=0; i<4096; i++){
		  DAC -> DHR12R1 |=i;
		  delay(168000);
	  }
	 if(i<=4096){
		 i=0;
	 }
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
