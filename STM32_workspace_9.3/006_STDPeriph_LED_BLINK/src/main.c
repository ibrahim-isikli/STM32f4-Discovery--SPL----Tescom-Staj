
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
//void GPIO_Config(void);

// Bu calismada REGISTER_LED_BLINK uygulamasindan farkli olarak STDPeriph lib kullanildi

 GPIO_InitTypeDef GPIO_InitStruct;  // GPIO pin registerlara ulasmak icin bir struct var
 	 	 	 	 	 	 	 	 	 // bu strcutta ->\GPIO_Pin\GPIO_Mode\GPIO_Speed\ GPIO_OType\GPIO_PuPd

void GPIO_Config(void){

	// RCC -> enable AHB1ENR peripheral clock fonksiyonu:
	// RCC_AHB1PeriphClockCmd();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	// RCC -> AHB1ENR bus enable -> GPIOD port D enable

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	// kullanilacak pinler cekilir (pin tanimlamasi)

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	// pin mode -> output | output | output | output ;

	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_100MHz;
	//GPIO registerlarini ayarladik

	GPIO_Init(GPIOD,&GPIO_InitStruct);
	// GPIO_Init(portD,*ptrStruct); -> Yukarda yaptiklarimizi init. eder
 }


int main(void)
{
	GPIO_Config();
  while (1)
  {
	  // pinleri logic 1 ve logic 0 seviyelerine cekmek icin 2 fonk kullanilir
	  // GPIO_SetBits() -> biti 1 yapar
	  // GPIO_ResetBits( -> biti 0 yapar

	  GPIO_SetBits(GPIOD,GPIO_Pin_12);
	  GPIO_SetBits(GPIOD,GPIO_Pin_13);
	  GPIO_SetBits(GPIOD,GPIO_Pin_14);
	  GPIO_SetBits(GPIOD,GPIO_Pin_15);


	  //GPIO_ResetBits();
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
