#include <stm32f103xb_gpio.h>
//#include <stdio.h>

//TIMER...........................................................................
#define SYSCLK_FREQ_72MHz	72
#define TICK_CLR_CHANGE		1      // Xus/tick
#define TICK_LED 			1      // Xus/tick

// for LED
#define PERIOD_CLR_CHANGE	15000  // 2500us
#define PERIOD_LED			2000
#define ARR_CLR_CHANGE		(PERIOD_CLR_CHANGE/TICK_CLR_CHANGE-1) 
#define ARR_LED		 		(PERIOD_LED/TICK_LED-1)



extern int ccr1_rLED, ccr3_gLED, ccr4_bLED;
extern int clr_change_FLAG;


void TIM3_config();
void TIM4_config();

int map(int var, int x0, int x1, int y0, int y1);
void dutyChange(int r, int g, int b, int idx);
//TIMER...........................................................................




// //USART...........................................................................
// extern int RXCcnt, Rxflag;
// extern char USART_readData[30];			
									
// void USART_config();
// //USART...........................................................................




//BASE.............................................................................
void RCC_config(uint32_t RCC_APB2Periph, uint32_t RCC_APB1Periph);
void GPIO_config(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIOmode);
void NVIC_Config(uint8_t, uint8_t, uint8_t);								
//BASE.............................................................................									

									