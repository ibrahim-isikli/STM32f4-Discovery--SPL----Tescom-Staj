#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef  ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

volatile uint16_t adc_value=0;
volatile float voltage=0;

 void RCC_Config(void);
 void GPIO_Config(void);
 void ADC_Config(void);
 uint16_t Read_ADC();

 void RCC_Config(void){
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); // PORTD enable
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // ADC1 enable
}

 void GPIO_Config(void){
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
 GPIO_Init(GPIOA,&GPIO_InitStruct);
}

 void ADC_Config(void){

	// ADC_CommonInitStruct.ADC_DMAAccessMode cpuya ugrasin DMA kullanilmayacak
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
    //ADC_CommonInitStruct.ADC_TwoSamplingDelay -> kullanilmiyor
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_8b; // Resolution= 8 bit
	ADC_Init(ADC1,&ADC_InitStruct);

	ADC_Cmd(ADC1,ENABLE);
}

 uint16_t Read_ADC(){

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_84Cycles);
	ADC_SoftwareStartConv(ADC1);

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)== RESET){

	}

	return ADC_GetConversionValue(ADC1);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();

  while (1)
  {
	  adc_value = Read_ADC();
	  voltage = (0.01294)*(adc_value);
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
