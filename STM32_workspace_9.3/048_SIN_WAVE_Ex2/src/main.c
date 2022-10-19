#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

static void RCC_Config(void);
static void GPIO_Config(void);
static void TIM_Config(void);
static void DAC1_Config(void);

static uint32_t count;

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
DAC_InitTypeDef DAC_InitStruct;

static void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
}

static void GPIO_Config(void){
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

static void TIM_Config(void){
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 3999;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 41999;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2,ENABLE);
}

static void DAC1_Config(void){
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1,&DAC_InitStruct);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}
/*
const uint16_t aSine12bit[32] = {
                      2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};*/


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
int i =0;

int main(void)
{
 	RCC_Config();
	GPIO_Config();
	TIM_Config();
	DAC1_Config();
  while (1)
  {		count=TIM_GetCounter(TIM2);
  	  for (i=0; i<101; i++){
	  DAC_SetChannel1Data(DAC_Align_12b_R,aSine12bit[i]);
	  i++;
  	  }
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
