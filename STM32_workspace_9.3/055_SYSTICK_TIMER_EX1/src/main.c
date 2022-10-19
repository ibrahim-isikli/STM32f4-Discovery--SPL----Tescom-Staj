/*

* Bu kod, insan gözünün hangi frekansý nasýl gördüðünü test etmek için yazýlmýþtýr.

* Pin_A_4'e frekansý kontrol edebilmek için potansiyemetrenin orta bacaðý baðlanmýþtýr

* STMStudio ile periyot ve frekans deðiþkeni gözlemlenerek potansiyometre ile çevrim yapýlabilir.

* stm32f4xx_it.c içerisindeki  void SysTick_Handler(void) fonksiyonunu yorum satýrý yaparak iki kere tanýmlanmasýný önleyiniz

*

*

* */

#include "stm32f4xx.h"

#include "stm32f4_discovery.h"





uint16_t count; // extern uint16_t count => stm32f4xx_it.c

uint16_t adc_value;

float period;

float frequence;





ADC_InitTypeDef ADC_InitStruct; // ADC structure is defined

GPIO_InitTypeDef GPIO_InitStruct;





void GPIO_Config(){



RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);



GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;

GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;



GPIO_Init(GPIOD,&GPIO_InitStruct);





RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); // GPIOA clock line anabled



GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; // Analog mode selected

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // PA0 selected

GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // Pull-up,Pull-down type selected

GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; // Pull-down selected

GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; // 100 MHz



GPIO_Init(GPIOA,&GPIO_InitStruct); //GPIO setting initialized



}



void delay_ms(uint32_t time){



count = time ;

while(count);

}





void SysTick_Handler(void)

{

/*  TimingDelay_Decrement(); */

if(count > 0){

count--;

}

}





void ADC_Config(){



RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);



ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;

ADC_InitStruct.ADC_Resolution = ADC_Resolution_6b;



ADC_Init(ADC1,&ADC_InitStruct); // GPIO setting initialized

ADC_Cmd(ADC1,ENABLE); //ADC Peripheral enabled



ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1 , ADC_SampleTime_56Cycles);

ADC_SoftwareStartConv(ADC1);



}





int main(void)

{

GPIO_Config();

SysTick_Config(SystemCoreClock/1000); //per milisecond

ADC_Config();



  while (1)

  {

  while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET); // Wait till the End Of Conversion



adc_value = ADC_GetConversionValue(ADC1); // Get value from potentiometer

frequence = adc_value+1;      // Hertz

period = (float) 1000*1/frequence; // in milisecond term



  GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);



  delay_ms(period);

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
