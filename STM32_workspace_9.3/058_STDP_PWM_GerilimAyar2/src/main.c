#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config(void);
void TIM_Config(void);
void SysTick_Handler(void);
void delay_ms(uint32_t time);

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIM_OC_InitStruct;

uint32_t delay_count;


void SysTick_Handler(void){
	if(delay_count>0){
		delay_count--;
	}
}

void delay_ms(uint32_t time){
	delay_count= time;
	while(delay_count);
}



void GPIO_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	// AF sectigimiz icin AF config yapmaliyiz
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	//  time olarak kullandigimiz icin alternate func -> AF secildi
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void TIM_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 84MHz tim4 clock olarak ayarladik
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 8399;

	//=========================================== HESAPLAMALAR ==========================//

	/* FORMUL:
	 *
	 * 	Period   = 	( Timer_tick_freq / PWM_freq ) -1
	 * 	PWM_freq =  Timer_tick_freq / ( period + 1)
	 * 	Timer_tick_freq  = TIMER_Clock / (prescaler + 1)
	 *
	 */

	/*TIMER_Clock = 84*10^6
	 * preclaeri 83 ayarlarsak
	 * 	Timer_tick_freq  = 84 000 000 / 84 = 1000 000
	 * 	period 99 ayarlarsak
	 * 	PWM_freq = 1000 000 / 100 = 10 000
	 * 	PWM frekansi 10 kHz oldu
	 * */

	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_InitStruct);
	TIM_Cmd(TIM4,ENABLE);

	// pwm ayarlari

	TIM_OC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStruct.TIM_OutputState = ENABLE;
	TIM_OC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // yukselen kenar

	SysTick_Config(SystemCoreClock/1000); // 1ms de 1 interrupta gir

}




int main(void)
{
	GPIO_Config();
	TIM_Config();
  while (1)
  {
	for(int i=0; i<=100; i++){

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC1Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC2Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC3Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC4Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);
	}

	for(int i=100; i>=0; i--){

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC1Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC2Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC3Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);

				TIM_OC_InitStruct.TIM_Pulse=i;
				TIM_OC4Init(TIM4,&TIM_OC_InitStruct);
				TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
				delay_ms(20);
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
