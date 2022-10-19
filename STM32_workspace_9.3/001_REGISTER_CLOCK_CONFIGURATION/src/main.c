#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;
uint32_t systemClock;

int main(void)
{
	systemClock = SystemCoreClock; 		// 168mHz -> HSE osilator enable oldugunu anla
	RCC_DeInit();						// HSI osilator enable, PLL off
	SystemCoreClockUpdate();		    // 16 mHZ
	systemClock =SystemCoreClock;

  while (1)
  {

  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){

  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){

  return -1;
}
