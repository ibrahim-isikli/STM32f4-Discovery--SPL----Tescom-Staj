#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config(void);
void DAC1_Config(void);
void CLCK_Config(void);
void delay (uint32_t time);

int i=0;

void CLCK_Config(void){
#if 0
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
#endif

#if 1
		/*RCC_CR (clock control register)*/
					RCC->CR |= 00010000;	// HSEON enable
					while(!(RCC->CR & 0x00020000));
						RCC->CR |= 0x00080000;

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
#endif
}

void RCC_Config(void){
	RCC->AHB1ENR |= 0x00000001; // portD enable
	RCC->APB1ENR |= 0x20000000; // DAC Enable
}


void DAC1_Config(void){
	 DAC->CR |= 0x00000001; // dac channel 1 enable
	 DAC->SWTRIGR |= 0x00000000; // dac software trigger disable
	 //dacý kac bit olarak kullanacagiz-> 12 bit saga yasli olarak
	 DAC->DHR12R1 |= 0x00000000; // dac channel 1 right aligned datayý burada bu sekilde saklicam
}

void delay (uint32_t time){
	while(time--);
}

int main(void)
{
	// a portunun 4. pini DAC1_channeldir
	CLCK_Config();
	RCC_Config();
	DAC1_Config();
    while (1)
  {
    	for(i=1; i<4096; i++){

    		DAC->DHR12R1 |= i;
    		delay(210000); // 100 ms de 1 artaracak
    		// ledin yanma seviyei yani cýkýstaki gerilim 0V tan 3.3V a 100  msde 1 artacak
    	}

    	i=0;
    	delay(21000000);
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
