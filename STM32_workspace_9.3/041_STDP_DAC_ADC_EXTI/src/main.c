#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

static void RCC_Config(void);
static void GPIO_Config(void);
static void DAC1_Config(void);
static void ADC_Config(void);
static uint16_t Read_ADC(void);
static void EXTI_Config(void);
static void NVIC_Config(void);
static void EXTI0_IRQHandler(void);
static void delay(uint32_t time);


static volatile uint16_t adc_value;

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
DAC_InitTypeDef DAC_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

static void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //GPIOA ENABLE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE); // DAC ENABLE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // ADC1 ENABLE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);  // EXTI ENABLE
}

static void GPIO_Config(void){
	// DAC
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//ADC
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	// EXTI0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//EXTI1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	// EXTI1 enable -> NVIC1 enable -> EXTI1_IRQHandler -> DAC && ADC
}

static void DAC1_Config(void){

	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1,&DAC_InitStruct);
	DAC_Cmd(DAC_Channel_1,ENABLE);

}

static void ADC_Config(void){
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);
	ADC_Cmd(ADC1,ENABLE);
}

static uint16_t Read_ADC(void){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)!=SET);
	return ADC_GetConversionValue(ADC1);
}

static void EXTI_Config(void){
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
}

static void NVIC_Config(void){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
}


static void EXTI0_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line0)== SET){

		DAC_SetChannel1Data(DAC_Align_12b_R,2047);
		delay(21000000);

		EXTI_ClearFlag(EXTI_Line0);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	DAC1_Config();
	ADC_Config();
	EXTI_Config();
	NVIC_Config();
  while (1)
  {
	  adc_value = Read_ADC();
	  DAC_SetChannel1Data(DAC_Align_12b_R,4095);
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
