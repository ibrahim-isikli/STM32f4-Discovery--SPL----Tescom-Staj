#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int count = 0;

void GPIO_Config(void){

		RCC->CR |= 0x00030000; 			// HSEON ve HSERDY set
		while(!(RCC->CR & 0x00020000)); // HSEON Ready Flag wait -----------------------------------------> buna gerek yok bu bit(HSERDY read-only) read-only
										// HSE kullanima hazir ise forever looptan cik (bu bir flagtir)

		RCC->CR |= 0x00080000; 			//CSS (clock security system )enable
		RCC->PLLCFGR |= 0x00400000; 		// PLL'i HSE sectik
		RCC->PLLCFGR |= 0x00000004;			// PLL M = 4
		RCC->PLLCFGR |=	0x00005A00;			// PLL N = 168
		RCC->PLLCFGR |=	0x00000000;			// PLL P = 2

		RCC->CFGR |= 0x00000000; //   AHB prescaler 1 oldu
		RCC->CFGR |= 0x00008000; //   apb2 prescaler (ppre2) (degeri 2 yaptik)
		RCC->CFGR |= 0x00001400; //   apb1 prescaler (degeri 4 yaptik)

		RCC->CIR |= 0x00080000; //HSERDY Flag clear
		RCC->CIR |= 0x00800000; //CSS Flag Clear

		RCC->AHB1ENR = 0x00000009; // GPIOA ve GPIOD enable

		// 12 13 14 15. pinler icin 01 yazip aktif edelim
		GPIOD->MODER = 0x55000000;
		GPIOD->OTYPER = 0x00000000; // pinler push pull
		GPIOD->OSPEEDR = 0xFF000000; // pinler very high speed
		GPIOD->PUPDR = 0x00000000; // pinler no pull

		// A portu deafult olarak input modundadir
}

void delay (uint32_t time){
	while(time--);
}

int main(void)
{
	GPIO_Config();
   while (1)
  {
     if(GPIOA->IDR & 0x00000001){
    	 while(GPIOA->IDR & 0x00000001);
    	 delay(1680000);

    	 count++;

     }

     if(count %2 == 0){
    	 GPIOD->ODR = 0x00000000;

     }

     else{
    	 GPIOD->ODR = 0x0000F000;
     }
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
