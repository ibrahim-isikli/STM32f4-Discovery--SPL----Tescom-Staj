

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;
uint32_t systemClock;

int main(void)
{
	systemClock=SystemCoreClock;
	RCC_DeInit(); // HSI Enable, PLL off
	SystemCoreClockUpdate(); // SystemCoreClock guncelle
	systemClock=SystemCoreClock;
	// pointer koy exp den incele
	// systemClock un 16MHz oldugunu goreceksin
	// HSE -> HSI gectik (osiltaorler)
  while (1)
  {

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
