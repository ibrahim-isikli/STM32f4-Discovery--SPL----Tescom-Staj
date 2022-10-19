#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config(void);
void DAC2_Config(void);
void delay(uint32_t time);
GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

int i=0;

void GPIO_Config(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void DAC2_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);

	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_2,&DAC_InitStruct);
	// a portunun 5. pini
	DAC_Cmd(DAC_Channel_2,ENABLE);
}

void delay(uint32_t time){
	while(time--);
}



int main(void)
{

  GPIO_Config();
  DAC2_Config();
  while (1)
  {
	  for(uint32_t i=0;i<250;i++){
	  DAC_SetChannel2Data(DAC_Align_8b_R,i);
			  delay(21000);
			  if(i==249){
				  for(uint32_t k=250;k>0;k--){
					  DAC_SetChannel2Data(DAC_Align_8b_R,k);
					  			  delay(21000);
				  }
			  }
	  }
/*
	  // 1 sn 1.5 volt
	  DAC_SetChannel2Data(DAC_Align_8b_R,255);
	  delay(21000000);
	  // 1 sn 0 volt
	  DAC_SetChannel2Data(DAC_Align_8b_R,0);
	  delay(21000000);
*/

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
