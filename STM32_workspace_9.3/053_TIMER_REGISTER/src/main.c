#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

 void RCC_Config(void);
 void TIM_Config(void);

uint16_t count;

 void RCC_Config(void){

		RCC->CR |= (1<<16); // HSEON enable
		while(!(RCC->CR & (1<<17)));
		RCC->CR |= (1<<19); //css enable
		RCC ->PLLCFGR |= (1<<22); // PLLSRC->HSE
		RCC->PLLCFGR |= (4<<0);  // PLl_M=4
		RCC->PLLCFGR |= (168<<6); // PLL_N =168
		RCC->PLLCFGR |= 0x00000000; // PLL_P=2
		RCC->CFGR |= 0x00000000; // not divided
		// bizim isimiz APB1 ile cunku DAC birimi

		RCC->CFGR |= (5<<10); // ppre1 -> APB1 divided 4
		RCC->CFGR |= (4<<13); //ppre2 -> APB2 divided 2
		RCC->CIR |= (1<<23); // CSS clear
		RCC->CIR |= (1<<19); //hse ready clear
}


 void TIM_Config(void){

	RCC->APB1ENR |= 1 << 0; //Timer2 clock enable


	TIM2->CR1 |= 0<<4; // counter  mode is up counter
	TIM2->CR1 |= 0<<5; //center aligned mode-> edge aligned
	TIM2->CR1 |= 0 << 8; // SET THE CLOCK DÝVÝSÝON 1

	TIM2->SMCR |= 0<<0; // ýnternal clock source
	TIM2->EGR |= 1<<0; //  timer uotade generation
	TIM2->PSC = 41999;
	TIM2->ARR =4000;

	TIM2->CR1 |= 1<<0; // counter 2 enable


}


int main(void)
{
  RCC_Config();
  TIM_Config();

  while (1)
  {
	  count = TIM2->CNT;
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
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
