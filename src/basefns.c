#include <stm32f103xb_gpio.h>
#include <misc_103xb.h>
#include <stm32f103xb_rcc.h>


void RCC_config(uint32_t RCC_APB2Periph, uint32_t RCC_APB1Periph)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
}


void GPIO_config(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIOmode)
{
	GPIO_InitTypeDef GPIO_InitStructure={0};	
	
	//user LED : A5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIOmode;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}


void NVIC_Config(uint8_t IRQnum, uint8_t preemptNum, uint8_t subNum)
{
	NVIC_InitTypeDef NVIC_InitStructure={0};

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = IRQnum;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemptNum;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = subNum;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

