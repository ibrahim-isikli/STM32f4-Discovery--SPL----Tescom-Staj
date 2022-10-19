#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
void RCC_Config(void);
void GPIO_Config(void);

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStructt;

void RCC_Config(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
}

void GPIO_Config(void){
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct)
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
  while (1)
  {

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
