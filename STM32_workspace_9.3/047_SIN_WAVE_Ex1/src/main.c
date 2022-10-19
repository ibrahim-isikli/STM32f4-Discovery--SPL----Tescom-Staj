#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config(void);
void DAC2_Config(void);


static uint32_t count;

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;



void GPIO_Config(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

// dac
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



const uint16_t aSine12bit[32] = {
                      2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};

int i = 0;
int main(void)
{
                           GPIO_Config();
  DAC2_Config();

  while (1)
  {
	  count = TIM_GetCounter(TIM3);
	  // 1 sn 1.5 volt
	  DAC_SetChannel2Data(DAC_Align_12b_R,2047);
	  DAC_SetChannel2Data(DAC_Align_12b_R,2447);
	  DAC_SetChannel2Data(DAC_Align_12b_R,2831);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3185);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3498);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3750);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3939);
	  DAC_SetChannel2Data(DAC_Align_12b_R,4056);
	  DAC_SetChannel2Data(DAC_Align_12b_R,4095);
	  DAC_SetChannel2Data(DAC_Align_12b_R,4056);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3939);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3750);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3495);
	  DAC_SetChannel2Data(DAC_Align_12b_R,3185);
	  DAC_SetChannel2Data(DAC_Align_12b_R,2831);
	  DAC_SetChannel2Data(DAC_Align_12b_R,2447);
	  DAC_SetChannel2Data(DAC_Align_12b_R,2047);
	  DAC_SetChannel2Data(DAC_Align_12b_R,1647);
	  DAC_SetChannel2Data(DAC_Align_12b_R,1263);
	  DAC_SetChannel2Data(DAC_Align_12b_R,909);
	  DAC_SetChannel2Data(DAC_Align_12b_R,599);
	  DAC_SetChannel2Data(DAC_Align_12b_R,344);
	  DAC_SetChannel2Data(DAC_Align_12b_R,155);
	  DAC_SetChannel2Data(DAC_Align_12b_R,38);
	  DAC_SetChannel2Data(DAC_Align_12b_R,0);
	  DAC_SetChannel2Data(DAC_Align_12b_R,38);
	  DAC_SetChannel2Data(DAC_Align_12b_R,155);
	  DAC_SetChannel2Data(DAC_Align_12b_R,344);
	  DAC_SetChannel2Data(DAC_Align_12b_R,599);
	  DAC_SetChannel2Data(DAC_Align_12b_R,909);
	  DAC_SetChannel2Data(DAC_Align_12b_R,1263);
	  DAC_SetChannel2Data(DAC_Align_12b_R,1647);


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
