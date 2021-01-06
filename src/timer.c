#include "user.h"

#include <stm32f103xb_tim.h>
#include <misc_103xb.h>


int ccr1_rLED = 1, ccr3_gLED=1, ccr4_bLED=1;
int	clr_change_FLAG;


void TIM3_config() 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure={0};
	uint16_t PrescalerValue = (uint16_t) (SYSCLK_FREQ_72MHz * TICK_CLR_CHANGE) - 1;
	
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = ARR_CLR_CHANGE;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
	TIM_Cmd(TIM3, ENABLE);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	NVIC_Config(TIM3_IRQn, 0, 0);
}


void TIM4_config() 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure={0};
	TIM_OCInitTypeDef  TIM_OCInitStructure={0};
	uint16_t PrescalerValue = (uint16_t) (SYSCLK_FREQ_72MHz * TICK_LED) - 1;
	
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = ARR_LED;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = ccr1_rLED;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
	TIM_OCInitStructure.TIM_Pulse = ccr3_gLED;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_Pulse = ccr4_bLED;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

	
/* ISR ********************************************************************************/
void TIM3_IRQHandler (void) {
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
	
	clr_change_FLAG=1;
} 
