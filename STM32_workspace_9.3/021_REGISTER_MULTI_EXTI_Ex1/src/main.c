#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


/************************SIKINTILI KOD BUNU DEBUG ETME*******************/

void RCC_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void delay (uint32_t time);

void RCC_Config(void){
	RCC->AHB1ENR |= (1<<0); // port A enable
	RCC->AHB1ENR |= (1<<3); // port D enable
	RCC->APB2ENR |= (1<<14); // APB2 bus clock enable SYSCFG
}


void GPIO_Config(void){
	//GPIOD
	GPIOD->MODER |= (55<<24);   // 15 14 13 12 output
	GPIOD->OTYPER = 0x00000000; // all them push pull
	GPIOD->OSPEEDR |= (255<<24); // 15 14 13 12 high speed
	GPIOD->PUPDR = 0x00000000; // all them NOPULL
	//GPIOA
	GPIOA->MODER = 0x00000000; // all pin input
	GPIOA->OTYPER = 0x00000000; // all them push pull
	GPIOA->OSPEEDR |= (63<<0); // 0 1 2 pin high speed
	GPIOA->PUPDR |= (42<<0); // 0 1 2 pin pull down
}

void EXTI_Config(void){
	NVIC_EnableIRQ(EXTI0_IRQn); //IRQ enable
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	SYSCFG->EXTICR[0]= 0x00000000; // [0] pin portA
	SYSCFG->EXTICR[1]= 0x00000000; // [1] pin port A
	SYSCFG->EXTICR[2]= 0x00000000; // [2] pin port A

	/*priority*/
	NVIC_SetPriority(EXTI0_IRQn,0); // en oncelikli
	NVIC_SetPriority(EXTI1_IRQn,1); //orta oncelikli
	NVIC_SetPriority(EXTI2_IRQn,2); // dusuk oncelikli

	//interrupt mask register (IMR) (interrupt or event)
	EXTI->IMR |= (7<<0);   // 0 1 2 ====selected===> interrupt
	EXTI->RTSR |= (7<<0); // 0 1 2 ====selected===> rising trigger
}

void EXTI0_IRQHandler(void){

	if(EXTI->PR & (1<<0)){ // flag control

		volatile uint8_t i=0;

		do{
			GPIOD->ODR |= (1<<15); // 15 pin set
			delay(16800000);
			GPIOD->ODR = 0x00000000; // all them reset
			delay(16800000);
			i++;
		}while(i<5);
		EXTI->PR |=(0<<0); // flag reset
	}
}

void EXTI1_IRQHandler(void){
	if(EXTI ->PR & (1<<1)){ // flag control

		volatile uint8_t i=0;

		do{
			GPIOD->ODR |=(1<<14); // 14. pin set
			delay(16800000);
			GPIOD->ODR = 0x00000000; // all them reset
			delay(16800000);
			i++;
		}while(i<5);
		EXTI->PR |= (0<<1); // flag reset
	}
}

void EXTI2_IRQHandler(void){
	if(EXTI->PR & (1<<2)){
		volatile uint8_t i=0;

		do{
			GPIOD->ODR |=(1<<13); // 13 pin set
			delay(16800000);
			GPIOD->ODR = 0x00000000; // all them reset
			delay(16800000);
			i++;
		}while(i<5);
		EXTI->PR |=(0<<2); //flag reset
	}
}

void delay (uint32_t time){
	while(time--);
}


int main(void)
{
	RCC_Config();
	GPIO_Config();
	EXTI_Config();
	EXTI0_IRQHandler();
	EXTI1_IRQHandler();
	EXTI2_IRQHandler();
    while (1)
  {

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
