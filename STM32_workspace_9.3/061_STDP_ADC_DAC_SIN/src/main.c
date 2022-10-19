#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "math.h"

void RCC_Config(void);
void GPIO_Config(void);
void ADC_Config(void);
void DAC2_Config(void);
uint32_t Read_ADC(void);
uint32_t Read_ADC2(void);

GPIO_InitTypeDef GPIO_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
ADC_InitTypeDef ADC_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

uint32_t adc_value;
float adc2_value;
float PiktoPik;
uint32_t sine_val[420];
#define pi 3.1415926

void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
}

void GPIO_Config(void){
	// DAC pa5
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	// ADC1 pa1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	// ADC2 pa2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void ADC_Config(void){

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1,&ADC_InitStruct);
	ADC_Cmd(ADC1,ENABLE);

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler =ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_8b;
	ADC_Init(ADC2,&ADC_InitStruct);
	ADC_Cmd(ADC2,ENABLE);
}

void DAC2_Config(void){
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_2,&DAC_InitStruct);
	DAC_Cmd(DAC_Channel_2,ENABLE);
}

uint32_t Read_ADC(void){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_3Cycles);
	ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
		return ADC_GetConversionValue(ADC1);

}

uint32_t Read_ADC2(void){
		ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_3Cycles);
		ADC_SoftwareStartConv(ADC2);

			while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == RESET);
			return ADC_GetConversionValue(ADC2);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	DAC2_Config();

  while (1)
  {
	  	adc_value= (Read_ADC()/1000);
	  	adc2_value = Read_ADC2() * (3.0/255);
	  	PiktoPik = adc2_value/3.0;
		for(int i=0;  i<420; i++){
			 sine_val[i]= (((PiktoPik*sin(i* adc_value*2*pi/420)) +1) *(4096/2) );
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
