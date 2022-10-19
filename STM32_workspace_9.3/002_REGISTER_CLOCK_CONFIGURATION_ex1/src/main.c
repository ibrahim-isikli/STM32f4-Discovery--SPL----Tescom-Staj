

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


// system_stm32f4xx.c deki SystemCoreClocku buraya extern ettim
// uint32_t SystemCoreClock = 168MHZ

extern uint32_t SystemCoreClock;

// SystemCoreClocku ide uzerinden takip edelim
// bunun icin systemClock adinda global bir degisken olusturalim

uint32_t systemClock;

int main(void)
{
	systemClock = SystemCoreClock;
	// buraya breakpoint koy incele (experessionda)
	// systemClock = 168000000 ( sistemi baslattigimda 168MHz'de osilatorum calisiyor)
	// Benim projem system_stm32f4xx.c deki SystemCoreClock ile HSI osilator ile baslatiliyor
	// 003'de bunu HSI ile nasil calistiracagimi anlattim

  while (1)
  {

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
