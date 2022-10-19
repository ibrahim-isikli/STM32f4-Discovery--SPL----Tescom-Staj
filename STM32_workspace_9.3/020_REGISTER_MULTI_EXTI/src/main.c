#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void delay (uint32_t);
void GPIO_Config(void);
void EXTI_Config(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);


void delay(uint32_t time){
	while(time--);
}

void GPIO_Config(void){

	RCC->AHB1ENR = 0x00000009;
	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0xFF000000;

}


void EXTI_Config(void){
	RCC->APB2ENR = 0x00004000;

	NVIC_EnableIRQ(EXTI0_IRQn);   // EXTI0 enable
	NVIC_EnableIRQ(EXTI1_IRQn);	  // EXTI1 enable
	NVIC_EnableIRQ(EXTI2_IRQn);   // EXTI2 enable

	SYSCFG->EXTICR[0] = 0x00000000; // EXTI_Line0 enable
	SYSCFG->EXTICR[1] = 0x00000000; // EXTI_Line1 enable
	SYSCFG->EXTICR[2] = 0x00000000; // EXTI_Line2 enable

	/*priority*/
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 3);
	NVIC_SetPriority(EXTI2_IRQn, 5);

	// interrupt mask register IMR (interrupt mý event mi olarak kullacagýz0> interrupt)
	EXTI->IMR = 0x00000007;
	// rising mi onu seciyoruz
	EXTI->RTSR = 0x00000007;
}

void EXTI0_IRQHandler(void){

	// flag control
	if(EXTI->PR & (1<<0)){
		volatile int i=0;

		do{
			GPIOD->ODR = 0x00001000;
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);
			i++;
		}while(i<5);

		EXTI->PR |= (1<<0); //flag reset
	}

}

void EXTI1_IRQHandler(void){
	// flag control
		if(EXTI->PR & (1<<1)){
			volatile int i=0;

			do{
				GPIOD->ODR = 0x00002000;
				delay(1680000);
				GPIOD->ODR = 0x00000000;
				delay(1680000);
				i++;
			}while(i<5);

			EXTI->PR |= (1<<1); //flag reset
		}
}

void EXTI2_IRQHandler(void){
	// flag control
		if(EXTI->PR & (1<<2)){
			volatile int i=0;

			do{
				GPIOD->ODR = 0x00008000;
				delay(1680000);
				GPIOD->ODR = 0x00000000;
				delay(1680000);
				i++;
			}while(i<5);

			EXTI->PR |= (1<<2); //flag reset
		}
}

int main(void)
{
  GPIO_Config();
  EXTI_Config();

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
