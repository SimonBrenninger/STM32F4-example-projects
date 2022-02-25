#include "header.h"

void TIM2_IRQHandler(void)
{
    // disable update interrupt pending flag
	if(TIM2->SR & TIM_SR_UIF)
    	TIM2->SR &= ~TIM_SR_UIF;

    GPIOC->ODR ^= GPIO_ODR_OD13;
}

void TIM2Config(void)
{
	// enable Timer 2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// make sure TIM2 is turned off
	TIM2->CR1 &= ~TIM_CR1_CEN;

	// timer clocked @ 48MHz
	// set prescaler to 48k --> count every ms
	TIM2->PSC = 48000;	// 48.000
	TIM2->ARR = 1000;	// count to 1000 (interrupt every 1000ms)

	// enable interrupt
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM2_IRQn, 0x03);
	NVIC_EnableIRQ(TIM2_IRQn);

	// counter enable
	TIM2->CR1 |= TIM_CR1_CEN;
}
