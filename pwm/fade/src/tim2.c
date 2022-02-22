#include "header.h"

void TIM2_IRQHandler(void)
{
    // disable update interrupt pending flag
	if(TIM2->SR & TIM_SR_UIF)
	{
    	TIM2->SR &= ~TIM_SR_UIF;
	}

	static int dir = 1;	// increase or decrease duty cycle
	int ccr2_buff;

	ccr2_buff = TIM2->CCR2 + dir*PWM_STEPS;

	// check if CCR2 would reached either end
	if(ccr2_buff < 0x0)
	{
		ccr2_buff = 0x0;		// prevent negative numbers
		dir = -dir;				// change dimming direction
	}
	else if(ccr2_buff > TIM2->ARR)
	{
		ccr2_buff = TIM2->ARR;	// prevent numbers greater than ARR
		dir = -dir;				// change dimming direction
	}
	TIM2->CCR2 = ccr2_buff;		// update CCR2 (duty cycle) register

	GPIOC->ODR ^= GPIO_ODR_OD13;	// dbg led
}

void TIM2Config(void)
{
	/* PWM Mode
	 * ARR = Frequency (~60Hz)
	 * CCRx = Duty Cycle (0%...100%)
	 * 
	 * enable pwm in OCxM
	 * preload OCxPE, arr-preload ARPE
	 * init with update event UG
	 * polarity in CCxP
	 * enable output by CCxE
	 * 
	 * PA1 @ TIM2 Ch2
	*/

	// enable Timer 2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// make sure TIM2 is turned off
	TIM2->CR1 &= ~TIM_CR1_CEN;
	// enable ARR preload
	TIM2->CR1 |= TIM_CR1_ARPE;

	// timer clocked @ 48MHz
	TIM2->PSC = 48;		// set prescaler to 48 --> count @ 1MHz (every us)
	TIM2->ARR = 16666;	// each pwm cycle @ 25Hz (40000us = 40ms)

	// reset OC2M bits (Output Compare Channel 2 Mode)
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M_Msk;
	// set OC1M to 0b110 (Output Commpare Channel 2 PWM Mode 1)
	TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	// enable preload register (update CCR2 only when event occurs)
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	// set polarity: active = high (CC2P = 0)
	TIM2->CCER &= ~TIM_CCER_CC2P;

	// CCR2 register sets duty cycle
	// (CCR2 = 0x0 --> 0% duty cycle; CCR2 = ARR --> 100% duty cycle)
	TIM2->CCR2 = 0x0;

	// enable capture/compare channel 2 interrupt
	TIM2->DIER |= TIM_DIER_UIE; //CC2IE UIE


	// capture/compare 2 output enable
	TIM2->CCER |= TIM_CCER_CC2E;

	NVIC_SetPriority(TIM2_IRQn, 0x03);
	NVIC_EnableIRQ(TIM2_IRQn);

	// reinintialze counter
	TIM2->EGR |= TIM_EGR_UG;

	// counter enable
	TIM2->CR1 |= TIM_CR1_CEN;
}