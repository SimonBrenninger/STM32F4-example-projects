#include "header.h"
#include "stm32f411xe.h"

static timer_callback_t cb = NULL;

void TIM5_IRQHandler(void)
{
	if(TIM5->SR & TIM_SR_UIF)
	{
		TIM5->SR &= ~TIM_SR_UIF;
	}


	// set flag interval_passed to start next measurement
	if (cb != NULL)
	{
		cb();
	}
}

void timer_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	// configure TIM5 to reset every 40 micro seconds

	TIM5->CR1 = 0x0;    // clock division to 1

	// set counter prescaler and auto-reload register
	TIM5->PSC = 0;		// 25MHz
	TIM5->ARR = 1000-1;	// 25MHz / 1000 = 25kHz -> INT every 40us

	// enable update interrupt
	TIM5->DIER |= TIM_DIER_UIE;

	// set nvic priority and enable interrupt handler
	NVIC_SetPriority(TIM5_IRQn, 57);
	NVIC_EnableIRQ(TIM5_IRQn);

	// enable timer 5 counter
	TIM5->CR1 |= TIM_CR1_CEN;
}

void timer_register_callback(timer_callback_t callback)
{
	if (callback != NULL)
	{
		cb = callback;
	}
}
