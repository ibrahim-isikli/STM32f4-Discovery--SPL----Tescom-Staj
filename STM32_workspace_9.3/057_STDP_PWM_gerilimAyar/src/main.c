/*
 * AHB1 clock freq->168MHz
 * APB1 clock freq -> 84 MHz
 * TIM4 clock freq -> 84 (div_1)
 * */


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void GPIO_Config(void);
void TIM_Config(void);

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStruct;
TIM_OCInitTypeDef TIM_OC_InitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	// GPIO_Mode_AF used -> must config PinAF (GPIOD_!2 -> TIM4_Channel_1)
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // alternate function mode
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

}

void TIM_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_TimeBase_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 84MHz
	TIM_TimeBase_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_InitStruct.TIM_Period=100-1;
	TIM_TimeBase_InitStruct.TIM_Prescaler=8400-1;
	TIM_TimeBase_InitStruct.TIM_RepetitionCounter = 0; //tekrarlama sayaci (N+1)
	TIM_TimeBaseInit(TIM4,&TIM_TimeBase_InitStruct);
	TIM_Cmd(TIM4,ENABLE);

	//=========================================== HESAPLAMALAR ==========================//
		/* FORMUL:
		 *
		 * 	Period   = 	( Timer_tick_freq / PWM_freq ) -1
		 * 	PWM_freq =  Timer_tick_freq / ( period + 1)
		 * 	Timer_tick_freq  = TIMER_Clock / (prescaler + 1)
		 *

		TIMER_Clock = 84*10^6
		 * preclaeri 8399 ayarlarsak
		 * 	Timer_tick_freq  = 84 000 000 / 8400 = 10 000
		 * 	period 99 ayarlarsak
		 * 	PWM_freq = 10 000 / 100 = 100Hz
		 * 	PWM frekansi 100 Hz oldu
		 *
		 */
	//======================================PWM Ayarlari ==========================//

	TIM_OC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;



}

int main(void)
{
	GPIO_Config();
	TIM_Config();
  while (1)
  {
	  // pulse =  [ (period +1 ) * (duty_cycle) ] - 1
	  	  // pulse = [(99 +1) * (duty_cycle)] - 1
	  	  // duty_cycle ý %50 olarak calistirmak isteyelim
	  	  // bunun icin pulse degeri :
	  	  // pulse = [(99 +1) * (50/100) ] -1
	  	  // duty_cycle %100 icin pulse degeri 49 olmali

	  TIM_OC_InitStruct.TIM_Pulse = 49;
	  TIM_OC1Init(TIM4,&TIM_OC_InitStruct);
	  TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable); //tim4 channel 1 enable
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
