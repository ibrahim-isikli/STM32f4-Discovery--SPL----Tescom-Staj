#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

 void GPIO_Config(void);
 void TIM_Config(void);
 void NVIC_Config(void);
 void TIM3_IRQHandler(void);

int count;

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

 void GPIO_Config(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void TIM_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 3999;
	TIM_InitStruct.TIM_Prescaler = 41999; // 2000 * 42 000 / 84 000 000 = 1sn
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_InitStruct);
	TIM_Cmd(TIM3,ENABLE);
}

void NVIC_Config(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); // ýnterruptla timeri baglama

	NVIC_Init(&NVIC_InitStruct);
}

  void TIM3_IRQHandler(void){

	GPIO_ToggleBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

int main(void)
{
	GPIO_Config();
	TIM_Config();
	NVIC_Config();
  while (1)
  {
	 count = TIM_GetCounter(TIM3);
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

  return -1;
}
