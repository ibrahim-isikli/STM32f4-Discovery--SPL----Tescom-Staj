#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// butona basýnca ledlerimiz 3sn yanip sonsun

GPIO_InitTypeDef GPIO_InitStruct; // GPIO nun structlari
EXTI_InitTypeDef EXTI_InitStruct; // externel interruptlþarin structlari
NVIC_InitTypeDef NVIC_InitStruct; // NVIC (interruptlari yoneten yonetci) structlari
void delay(uint32_t time);
void GPIO_Config(void){

							/*RCC_AHB1/APB2 ve GPIO COnfigurasyonlari*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //external interrupt syscfg olarak geciyor
	//NVIC neden aktif etmiyoruz -> islemciye dahildir.Bagli oldugu bir bus clock yok

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void EXTI_Config(void){
							/*  Externel Interrupt Configurasyonlari  */

																		// hangi GPIO pinini EXTI Line olarak kullanacaksan, bu fonk ile secmen lazim
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
																		// a portunun 0. pinini external interrupt olarak kullancagimi soylemis oldum
		EXTI_InitStruct.EXTI_Line = EXTI_Line0;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; 			// yukselen kenarda interrupta girecek

		EXTI_Init(&EXTI_InitStruct);

									/*NVIC (interrupt yoneticisi) Config*/
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0 ;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
	// sondaki iki ifade birden fazla interrupt kullandigimiz zaman devereye girer
	// inerrupt oncelik belirtme(sirasi)
	// Hangi interrupttun önceligini daha yuksek secme3k isttiyorsak
	//onun PreemptionPriority degerini daha dusuk girmeliyiz -> ne kadar dusuk o kadar oncelikli

	NVIC_Init(&NVIC_InitStruct);

	// external interrupt icin tum konfig tamamlandi
}

void EXTI0_IRQHandler(){
	// flag kontrol etmemiz gerek -> EXTI_GetITStatus

	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);

		EXTI_ClearITPendingBit(EXTI_Line0); // EXTI flag temzilemeyliyiz ki, daha sonra da calisabilsin
	}
}


void delay(uint32_t time){
	while(time--);
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	  GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
// interrupta girmeden once ledlerimiz yanacak,
//interrupta girdigimizde ledler 3 sn yanip sonecek
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
