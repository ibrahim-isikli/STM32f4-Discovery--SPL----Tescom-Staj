
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*********NOT***************/
/*
 * ====================================RCC clock control register (RCC_CR)===================
 *  HSEON 16. bit
 *  HSERDY 17.bit
 *  binary -> 00000000000000110000000000000000 ile veyalanmalý ki
 *  16. ve 17. bit set olsun
 *  0000 0000 0000 0011 0000 0000 0000 0000
 *  0     0    0    3   0     0   0    0   => 0x 00030000
 *
 *  CSS 19. bit
 *  0000 0000 0000 1000 0000 0000 0000 0000 => 0x00080000
 *  =========================================================================================
 *
 *
 *
 *  =====================================RCC_PLL REGISTER CONFIH=============================
 *
 *  PLLSRC 22. bit bu PLL SOURCE'dur. HSE ve HSI gecisi ayarlar
 *  0: HSI
 *  1: HSE
 *  0000 0000 0100 0000 0000 0000 0000 0000
 *  0     0     4    0    0    0    0    0
 *
 * 		f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
 *		f(PLL general clock output) = f(VCO clock) / PLLP
 * 		f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
 *
 *
 *   PLL M
 *   ---------------------------------------------------------------
 *   |        |         |          |         |         |            |
 *       PLLM5   PLLM4     PLLM3     PLLM2        PLLM1       PLLM0
 *   5.bit															0.bit
 *
 *   ornegin PLL_M 'i 4 e ayarlamak istiyorsan 0000 0000 0000 0000 0000 0000 0000 0010 = 4
 */

void CLK_Config(void){

	/**********************RCC_CONTROL REGISTER CONFIG****************************/

	RCC->CR |= 0x00030000; 			// HSEON ve HSERDY set
	while(!(RCC->CR & 0x00020000)); // HSEON Ready Flag wait -----------------------------------------> buna gerek yok bu bit(HSERDY read-only) read-only
									// HSE kullanima hazir ise forever looptan cik (bu bir flagtir)
	RCC->CR |= 0x00080000; 			//CSS (clock security system )enable

	/*************************************************************************/


	/**********************RCC_PLL REGISTER CONFIG****************************/

	RCC->PLLCFGR |= 0x00400000; 		// PLL'i HSE sectik
	RCC->PLLCFGR |= 0x00000004;			// PLL M = 4
    RCC->PLLCFGR |=	0x00005A00;			// PLL N = 168
    RCC->PLLCFGR |=	0x00000000;			// PLL P = 2

    /********************************************************************/


    /**********************RCC_CFGR Clock Config REGISTER CONFIG****************************/

    // AHB Prescaler 4 ile 7. bit arasinda , bunu 1 yapmak icin 0x00000000 giriyoruz
    RCC->CFGR |= 0x00000000; // AHB prescaler 1 oldu
    RCC->CFGR |= 0x00008000; //   apb2 prescaler (ppre2) (degeri 2 yaptik)
    RCC->CFGR |= 0x00001400; //   apb1 prescaler (degeri 4 yaptik)

    /**************************************************************************************/


    /**********************RCC_CIR Clock Interrupt REGISTER CONFIG****************************/

    // HSERDYC HSE ready ve CSSC (clock security) bir interrupttýr bunun temizlenmesi gerekir bunun icin
    // HSERDYC, HSE ready interrupt clear 0: No effect 1:HSERDYF cleared (19.bit)
    // CSSC 23. bit

    RCC->CIR |= 0x00080000; //HSERDY Flag clear
    RCC->CIR |= 0x00800000; //CSS Flag Clear

    /******************************************************************************************/

    /*clock ve pll  ayarlarindan sonra databus ayarlari gelir*/

    /*******************************RCC_AHB1RSTR***********************************************/

    // GPIOD 3. biti 1 yapalim -> portD enable

    RCC->AHB1ENR = 0x00000008;

    	GPIOD-> MODER = 0x55000000;  // 15 14 13 12 pinleri (01 alarak output ayarladik)
    	GPIOD->OTYPER = 0x00000000; // tum pinler output push pull (reset state)
    	GPIOD->OSPEEDR = 0xFF000000; //  15 14 13 12 pinleri (11 alarak high speed ayarladik)
    	GPIOD->PUPDR = 0x00000000; // hepsi 00 no pull aup no pull down
}

void delay(uint32_t time){
	while(time--);
}


int main(void)
{
  CLK_Config();

  while (1)
  {
	  	  GPIOD->ODR=0x0000F000;
	  	  delay(16800000);
	  	  GPIOD->ODR=0x00000000;
	  	  delay(16800000);
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
