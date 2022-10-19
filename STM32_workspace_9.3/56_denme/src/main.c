/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2022-09-02

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "STM32F4xx.h"

int CNTR;

/*****************************************************************************************************
         CPU PLL ile 168Mhz de kosturulur
         AHB frekansy 168 Mhz
         APB1 frekansy 42 Mhz
         APB2 frekansy 84 Mhz
*****************************************************************************************************/


void TIM7_IRQHandler()
{
    TIM7->SR=0;                       // Timer Int Flagini silelim
    CNTR++;
    CNTR&=0x3FF;
    DAC->DHR12R1=CNTR;
}

int main()
{
    while(1);
}














/*
 * void SystemInit(void)
{
	unsigned int i;
	     for (i=0;i<0x00100000;i++);     // OSC oturtma ve kurtarma rutini
	     RCC->CFGR |= 0x00009400;        // AHB ve APB hizlarini max degerlere set edelim
	     RCC->CR |= 0x00010000;          // HSE Xtal osc calismaya baslasin
	     while (!(RCC->CR & 0x00020000));// Xtal osc stabil hale gelsin
	     RCC->PLLCFGR = 0x07402A04;      // PLL katsayilarini M=4, N=168, P=2 ve Q=7 yapalim
	     RCC->CR |= 0x01000000;          // PLL calismaya baslasin  (Rehber Sayfa 95)
	     while(!(RCC->CR & 0x02000000)); // Pll hazir oluncaya kadar bekle
	     FLASH->ACR = 0x00000605;        // Flash ROM icin 5 Wait state secelim ve ART yi aktif edelim (Rehber Sayfa 55)
	     RCC->CFGR |= 0x00000002;        // Sistem Clk u PLL uzerinden besleyelim
	     while ((RCC->CFGR & 0x0000000F) != 0x0000000A); // Besleninceye kadar bekle
	     RCC->AHB1ENR |= 0x0000000F;     // GPIO A,B,C,D clock'u aktif edelim
	     GPIOD->MODER  = 0x55550000;     // GPIOD nin 15, 14, 13, 12, 11, 10, 9, 8 pinleri cikis tanimlandi (LEDler icin)
	     GPIOD->OSPEEDR= 0xFFFFFFFF;     // GPIOD nin tum cikislari en yuksek hizda kullanacagiz

	//   DAC1 kullanacagiz

	     GPIOA->MODER=0xA8000200;        // GPIOA4 Analog inp yapildi
	     RCC->APB1ENR|=1<<29;            // Artislik olsun (0x20000000 ile OR yap demek)
	     DAC->CR=0x00000003;             // DAC1 ve Bufferi aktif edelim

	//   Timer 7 ile calisalim

	     RCC->APB1ENR|=0x00000020;       // Timer7 CLK'u aktif edelim (84 Mhz)
	     TIM7->CR1=0x0080;               // Otomatik Reload
	     TIM7->PSC =839;                 // Prescaler degerimiz 839, Count frekansimiz = fCK_PSC / (Yuklenen Deger + 1) 84E6 / (840) = 100 KHz
	     TIM7->ARR =1;                   // Counter, Decimal 1 olunca basa donsun. Her 20 mikrosaniye de bir timer int olusacak.
	     TIM7->DIER=0x0001;              // Update Int enable
	     NVIC->ISER[1] = 0X00800000;     // NVIC de Timer 7 interrupta izin verelim
	     TIM7->CR1|=0x0001;              // Counter Enable
  }
 *
 */

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