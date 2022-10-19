#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
uint16_t count;

void GPIO_Config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}
void delay_ms(uint32_t time){
	count =time;
	while(count);
}
void SysTick_Handler(void)
{
	// 1 ms de bir buraya gelir
	if(count>0){
		count--;
	}
/*  TimingDelay_Decrement(); */
}
int main(void)
{
	GPIO_Config();
	SysTick_Config(SystemCoreClock/1000);
	// SystemCoreClock/1000 =>  1 milisaniyede 1 interrupta girer
	// scc / 100 000  10   -> 10 us
	// scc / 1 000 000 -> 1us
  while (1)
  {
	  GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  delay_ms(1000); //1000 ms 1 ledler yanip sonsun
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
