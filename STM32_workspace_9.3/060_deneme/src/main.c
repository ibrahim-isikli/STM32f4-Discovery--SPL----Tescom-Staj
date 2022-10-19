#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

 void GPIO_Config(void);
 void TIM_Config(void);
 void NVIC_Config(void);
 void TIM3_IRQHandler(void);
 static void DAC1_Config(void);

int count;


const float aSine12bit[101] = {
		2048.000,
		  2304.700,
		  2557.300,
		  2801.900,
		  3034.600,
		  3251.800,
		  3450.000,
		  3626.000,
		  3777.200,
		  3901.100,
		  3995.800,
		  4059.700,
		  4092.000,
		  4092.000,
		  4059.700,
		  3995.800,
		  3901.100,
		  3777.200,
		  3626.000,
		  3450.000,
		  3251.800,
		  3034.600,
		  2801.900,
		  2557.300,
		  2304.700,
		  2048.000,
		  1791.300,
		  1538.700,
		  1294.100,
		  1061.400,
		   844.200,
		   646.000,
		   470.000,
		   318.800,
		   194.900,
		   100.200,
		    36.300,
		    4.000,
		    4.000,
		    36.300,
		   100.200,
		   194.900,
		   318.800,
		   470.000,
		   646.000,
		   844.200,
		  1061.400,
		  1294.100,
		  1538.700,
		  1791.300,
		  2048.000,
		  2304.700,
		  2557.300,
		  2801.900,
		  3034.600,
		  3251.800,
		  3450.000,
		  3626.000,
		  3777.200,
		  3901.100,
		  3995.800,
		  4059.700,
		  4092.000,
		  4092.000,
		  4059.700,
		  3995.800,
		  3901.100,
		  3777.200,
		  3626.000,
		  3450.000,
		  3251.800,
		  3034.600,
		  2801.900,
		  2557.300,
		  2304.700,
		  2048.000,
		  1791.300,
		  1538.700,
		  1294.100,
		  1061.400,
		   844.200,
		   646.000,
		   470.000,
		   318.800,
		   194.900,
		   100.200,
		    36.300,
		    4.000,
		    4.000,
		    36.300,
		   100.200,
		   194.900,
		   318.800,
		   470.000,
		   646.000,
		   844.200,
		  1061.400,
		  1294.100,
		  1538.700,
		  1791.300,
		  2048.000
                      };

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

 void GPIO_Config(void){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void TIM_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 1999;
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

void DAC1_Config(void){
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1,&DAC_InitStruct);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}

  void TIM3_IRQHandler(void){

	  for (int i=0; i<4096; i++){
	  	  DAC_SetChannel1Data(DAC_Align_12b_R,i);
	  	  i++;

	    	  }
	  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

}

int main(void)
{
	GPIO_Config();
	TIM_Config();
	NVIC_Config();
	DAC1_Config();
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
