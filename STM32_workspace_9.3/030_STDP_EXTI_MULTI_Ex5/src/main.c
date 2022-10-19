#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

uint8_t count=0;

void RCC_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_Config(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

void USER_Default(void);
void delay (uint32_t time);

void RCC_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
}

void GPIO_Config(void){

	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_10| GPIO_Pin_11 |
			GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void EXTI_Config(void){

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	EXTI_InitStruct.EXTI_Line =EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource3);
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt,
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource4);
	EXTI_InitStruct.EXTI_Line=EXTI_Line4;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
}

void NVIC_Config(void){


	// not : subpriority interruptlarin onunu kesemez
	// interruptlarin önünü kesmeden, diger interruptlar goreivini bitirdiginde
	// maine gecmeden direkt olarak sub prioritye gecer

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// 2 bits for pre-emption priority
	// 2 bits for subpriority

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void delay (uint32_t time){
	while(time--);
}

void USER_Default(void){
		GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
		delay(1680000);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11);
		delay(1680000);
}

void EXTI0_IRQHandler(void){

	if (EXTI_GetFlagStatus(EXTI_Line0) == SET){

		do{
			GPIO_ResetBits(GPIOD,GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_12);
			delay(16800000);
			GPIO_ResetBits(GPIOD,GPIO_Pin_12);
			delay(16800000);
			count++;
		}while(count<3);

		count=0;
		EXTI_ClearFlag(EXTI_Line0);

	}
}

void EXTI1_IRQHandler(void){

	if(EXTI_GetFlagStatus(EXTI_Line1)==SET){

		do{
			GPIO_ResetBits(GPIOD,GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_13);
			delay(16800000);
			GPIO_ResetBits(GPIOD,GPIO_Pin_13);
			delay(16800000);
			count++;
		}while(count<5);
		count=0;
		EXTI_ClearFlag(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line2)== SET){

		do{
			GPIO_ResetBits(GPIOD,GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			delay(16800000);
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);
			delay(16800000);
			count++;
		}while(count<5);
		EXTI_ClearFlag(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line3)== SET){

		do{
			GPIO_ResetBits(GPIOD,GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			delay(16800000);
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);
			delay(16800000);
			count++;
		}while(count<5);
		EXTI_ClearFlag(EXTI_Line3);
	}
}


int main(void)
{
	RCC_Config();
	GPIO_Config();
	EXTI_Config();
	NVIC_Config();
  while (1)
  {
	  USER_Default();
  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
