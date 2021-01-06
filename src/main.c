#include "user.h"
#include <stm32f103xb_rcc.h>


int main() {
	int color[3]={0xFF, 0, 0}, idx=0; 
	
	// //USART CONFIG FOR DEBUG....................................
	// RCC_config(RCC_APB2Periph_GPIOA, RCC_APB1Periph_USART2);	
	// GPIO_config(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP);
	// GPIO_config(GPIOA, GPIO_Pin_3, GPIO_Mode_IN_FLOATING);	
	// USART_config(USART2);	
	// //USART CONFIG FOR DEBUG END................................
	
	//RGB LED CONFIG................
	RCC_config(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM3);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	GPIO_config(GPIOB, GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 , GPIO_Mode_AF_PP);
	//PB4 : only update : TIM3(CH1) : remap, update INT
	//PB6 : PWM : TIM4(CH1) 
	//PB8 : PWM : TIM4(CH3)
	//PB9 : PWM : TIM4(CH4)
	

	TIM4_config();
	TIM3_config();
	//RGB LED CONFIG END............
	
	
	while(1) {
		if(clr_change_FLAG) {		
			clr_change_FLAG=0;
			
			color[(idx+1)%3]=0xFF-(color[idx%3])--;
			dutyChange(color[0], color[1], color[2], idx);
			
			if(color[(idx+1)%3]>=0xFE)		++idx, idx%=3;
		}
	}
}


int map(int var, int x0, int x1, int y0, int y1)
{
	return ((y1 - y0)/(x1 - x0) * (var - x0) + y0);
}


void dutyChange(int r, int g, int b, int idx)
{
	if(idx==0) {
		TIM4->CCR1=ccr1_rLED=map(r, 0, 0xFF, 0, ARR_LED);
		TIM4->CCR3=ccr3_gLED=map(g, 0, 0xFF, 0, ARR_LED);
	}
	else if(idx==1) {
		TIM4->CCR3=ccr3_gLED=map(g, 0, 0xFF, 0, ARR_LED);
		TIM4->CCR4=ccr4_bLED=map(b, 0, 0xFF, 0, ARR_LED);
	}
	else if(idx==2) {
		TIM4->CCR4=ccr4_bLED=map(b, 0, 0xFF, 0, ARR_LED);
		TIM4->CCR1=ccr1_rLED=map(r, 0, 0xFF, 0, ARR_LED);
	}
}