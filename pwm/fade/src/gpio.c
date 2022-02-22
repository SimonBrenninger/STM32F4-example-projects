#include "header.h"

void GPIOConfig(void)
{
	// enable GPIO clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	// reset PA1 mode
	GPIOA->MODER &= ~GPIO_MODER_MODER1_Msk;
	// set PA1 as alternate mode (MODER1 = xs0b10)
	GPIOA->MODER |= GPIO_MODER_MODER1_1;
	// set PA1 output type to push-pull (OT1 = 0)
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT1;
	// configure alternate function on pin PA1 (AF01 = TIM2_CH2 according to datasheet)
	// for AF01: set AFRL1 (AFSEL1) to 0b0001
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL1_Msk;
	GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL1_0;

	// set PC13 (dbg led)
	GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT13;
}