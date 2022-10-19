
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config();

uint8_t adc_value;

void RCC_Config(){
#if 0
	//HSE ON and  CSS on :
	RCC->CR |= (9<<16);

	RCC->PLLCFGR |= (1<<22); // PLLSOURCE =selected=> HSE
	RCC->PLLCFGR |= (1<2); // PLL_M =4
	RCC->PLLCFGR |= (168<5); // PLL_N =168
	// PLL_P =2

	// prescaler ayarlari
	RCC->CFGR |= 0x00000000;// hpre prescaler
	RCC->CFGR |= (1<<15);// ppre1 (APB low speed prescaler APB1)
	RCC->CFGR |= (5<<10);// ppre2  (APB high speed prescaler APB2)

	RCC->CIR |= (17<<3); //HSE Ready ve CSS flag clear

#endif

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

}

void GPIO_Config(){
	RCC->AHB1ENR |= 0x00000001; //gpýoA enable
	GPIOA->MODER |= 0x00000003;  // mode AN
	GPIOA->OSPEEDR |=0x00000003; // high speed
}

void ADC_Config(){
	RCC->APB2ENR |= 0x00000100; //ADC1 clock enable

	ADC1->CR1 |= 0x02000000;  // resulotin  8bit
	ADC1->CR2 |= 0x00000001; //ADC ENABLE
	// prescaler div4 ADCPRE 17 16.bitler -> 01 olamli
	ADC->CCR |= 0x00010000; //div4
}


uint8_t Read_ADC(){

	uint8_t value=0;

	ADC1->CR2 |= (1<<30);

	while(!(ADC1->SR && 0x00000002)); //flag kalkana kadar bekle

	value= ADC1->DR;

	return value;
}

int main(void)
{

	RCC_Config();
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value =Read_ADC();
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
