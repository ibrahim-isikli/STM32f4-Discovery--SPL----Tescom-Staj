#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
TIM_OCInitTypeDef TIM_OCInitStruct;

void GPIO_Config(void);
void TIM_Config(void);
void RCC_COnfig(void);

void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
}

void GPIO_Config(void){
	// alternate func config
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // timer olarak kullanimlarda alternate func secilir
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void TIM_Config(void){
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 84MHZ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period =8399;
	TIM_TimeBaseInitStruct.TIM_Prescaler=99;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; //saymayi tekrarlama
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM4,ENABLE);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // mod1
	TIM_OCInitStruct.TIM_OutputState = ENABLE;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

	// timer clock 84 000 000 eger  prescaler 8399 secilirse
	// timer tick freq = Timer clock frekansi / (prescaler +1)
	// 84 000 000 / 8400 = 10 000 (Timer Tick Frekansi)
	// pwm freq = timer tick freq / (period +1)
	//  periyot 99 secilirse
	// pwm freq = 10 000 / 100  => pwm freq = 100 Hz

	// pulse = [ (periyot + 1) * (duty cycle) ]-1
	// [(99+1) * dc ]-1
	// duty cycle 50/100 secilsin
	// [100 * (50/100)]-1 = 43
	// pulse degerim 49 olmali
}


int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();

  while (1)
  {
	// PD 12
	  TIM_OCInitStruct.TIM_Pulse=49;
	  TIM_OC1Init(TIM4,&TIM_OCInitStruct);
	  TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable); // tim1_CH1 -> %50 dc


		// PD 13
		  TIM_OCInitStruct.TIM_Pulse=74;
		  TIM_OC2Init(TIM4,&TIM_OCInitStruct);
		  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable); // tim1_CH1 -> %75 dc

			// PD 14
			  TIM_OCInitStruct.TIM_Pulse=24;
			  TIM_OC3Init(TIM4,&TIM_OCInitStruct);
			  TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable); // tim1_CH1 -> %25 dc


				// PD 15
				  TIM_OCInitStruct.TIM_Pulse=99;
				  TIM_OC4Init(TIM4,&TIM_OCInitStruct);
				  TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable); // tim1_CH1 -> %100 dc
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
