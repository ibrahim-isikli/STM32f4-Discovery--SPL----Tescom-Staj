#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void TIMER_Config(void);

TIM_TimeBaseInitTypeDef TIM_InitStruct;

int count=0;

void TIMER_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 1999; //auto reloaded
	//1999 a kadar sayacak
	TIM_InitStruct.TIM_Prescaler =  41999;
	TIM_InitStruct.TIM_RepetitionCounter = 0; // kac defada bir tekrarlanacagini soyle
	//TIM_RepetitionCounter +1 -> her 1999 cycle da 1 tasma yap
	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);
	TIM_Cmd(TIM2,ENABLE);
}

// formul
// saniye = (periyot degeri +1) * (prescaler +1) / (clock hizi)
// apb1 42 mhz ama prescaler 1 den farkli -> timer  clock speed 84mhz
// 1  = ( +1) * ( +1)/84000000

// 1  = ( 1999+1) * ( 41999+1)/84000000
// 1 saniyede 1 -> 2000 e kadar sayan deger

int main(void)
{
	TIMER_Config();
  while (1)
  {
	 count = TIM_GetCounter(TIM2);
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
