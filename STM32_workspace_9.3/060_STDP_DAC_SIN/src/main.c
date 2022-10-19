#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "math.h"


void RCC_Config(void);
void GPIO_Config(void);
void DAC2_Config(void);

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

uint16_t count;
uint32_t sine_val[100];
#define pi 3.1415926

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
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void DAC2_Config(void){
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_Init(DAC_Channel_2,&DAC_InitStruct);
	DAC_Cmd(DAC_Channel_2,ENABLE);
}

void delay_ms(uint32_t time){
	count = time;
	while(count);
}


void SysTick_Handler(void)
{
	// 1 ms de bir buraya gelir
	if(count>0){
		count--;
	}
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	DAC2_Config();
	SysTick_Config(SystemCoreClock/1000);

  while (1)
  {
				for(int i=0;  i<100; i++){
					 sine_val[i]= ( ((sin(i*2*pi/100)) + 1 ) *(4096/2) );
					 DAC_SetChannel2Data(DAC_Align_12b_R,sine_val[i]);
				}
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
