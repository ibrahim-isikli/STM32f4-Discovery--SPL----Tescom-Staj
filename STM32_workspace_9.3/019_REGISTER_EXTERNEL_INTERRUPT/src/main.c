
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void delay(uint32_t time);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);

void CLK_Config(void){

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

void GPIO_Config(void){

	RCC->AHB1ENR |= 0x00000009;  // gpýoA ve gpýoD aktif
	GPIOD->MODER |= 0x55000000; // pin 12 13 14 15 output
	GPIOD->OTYPER |= 0x00000000; //pp
	GPIOD->PUPDR |= 0x00000000; // NOPULL
	GPIOD->OSPEEDR |= 0xFF000000; // high spped
}

void EXTI_Config(void){

	RCC->APB2ENR = 0x00004000; // SYSCFG enable

	SYSCFG->EXTICR[0] = 0x00000000;
	SYSCFG->EXTICR[1] = 0x00000000;
	SYSCFG->EXTICR[2] = 0x00000000;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	// interruptlarin oncelikleri

	NVIC_SetPriority(EXTI0_IRQn,0); // en onemli
	NVIC_SetPriority(EXTI1_IRQn,1); // orta onemli
	NVIC_SetPriority(EXTI2_IRQn,2); // en onemsiz

	EXTI->IMR |= 0x00000007;  // interrupt olarak mi kullanacaksin yoksa evetn mi
						   // 0 1 2 (MR0 MR1 MR2) 1 olsun ki interrupt olarak kullanalim

	EXTI->RTSR |= 0x00000007; // rising olarak ayarladik (0 1 2yi)
}

void delay(uint32_t time){
	while(time--);
}

void EXTI0_IRQHandler(void){

	if(EXTI->PR & 0x00000001) { //flag control
		GPIOD->ODR = 0x00001000;
		delay(33600000);
		EXTI->PR =  0x00000001; // flag reset
	}
}

void EXTI1_IRQHandler(void){

	if(EXTI->PR & 0x00000002){ //flag control
		GPIOD->ODR = 0x00002000;
		delay(33600000);
		EXTI->PR = 0x00000002; // flag reset
	}
}

void EXTI2_IRQHandler(void){
	if(EXTI->PR & 0x00000004){ //flag control
		GPIOD->ODR = 0x00004000;
		delay(33600000);
		EXTI->PR = 0x00000004; //flag reset
	}
}

int main(void)
{

	 CLK_Config();
 	 GPIO_Config();
 	 EXTI_Config();
  while (1)
  {
	GPIOD->ODR |= 0x0000F000; // hepsi set
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
