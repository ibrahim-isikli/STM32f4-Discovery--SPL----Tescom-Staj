/****** 12 bitlik ADC OKUMA (potansiyometre kullanarak)****/

// stm32f4 mikrodenetleyicisi en fazla ADC cozunurlugu 12 bittir (/12/10/8/6bit)
// 12 bit cozunurluk(resolution) -> 12 Cycle (ADC Cevrim Hizi)
// ADC referans voltajý 3.3V
// ADC stabil olarak 0V-3.3V araligini olcer
// 3.6V kadar da olcum yapabilmektedir
// resolution ->  Vref (2^n-1)				n-> /12/10/8/6bit

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
void GPIO_Config(void);
void GPIO_Config(void);

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t ses=0;
float  adc_voltage;

void GPIO_Config(void){
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
 GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void ADC_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);
}


uint16_t Read_ADC(){
	//  ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET){ //flag control

	}

	return ADC_GetConversionValue(ADC1);

}

int main(void)
{
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	ses = Read_ADC();
	//adc_voltage= (0.000805) * adc_value;
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
