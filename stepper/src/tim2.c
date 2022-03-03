#include "header.h"

void TIM2_IRQHandler(void)
{
    // disable update interrupt pending flag
	if(TIM2->SR & TIM_SR_UIF)
	{
    	TIM2->SR &= ~TIM_SR_UIF;
	}

	/*static uint8_t phase_locked = 0;	// indicate which phase is not changing

	if(phase_locked == 0)
	{
		// phase 0 is locked (bit 2 and bit 1)
		// bit 3 and 0 need to be flipped
		GPIOA->ODR ^= (STEPPER_PIN_3 | STEPPER_PIN_0);
		// lock other phase the next time
		phase_locked = 1;
	}
	else
	{
		// phase 1 is locked (bit 3 and bit 0)
		// bit 2 and 1 need to be flipped
		GPIOA->ODR ^= (STEPPER_PIN_2 | STEPPER_PIN_1);
		// lock other phase the next time
		phase_locked = 0;
	}*/

	static uint8_t motor_pins = 0b1000;

	// ouput new motor pin levels (only use first 4 bits)
	GPIOA->ODR &= ~(0xF << GPIO_ODR_OD0_Pos);
	GPIOA->ODR |= ((0xF & motor_pins) << GPIO_ODR_OD0_Pos);

	// shift motor pin levels
	motor_pins <<= 1;

	if(motor_pins > 0xF)
		motor_pins = 0b0001;

	GPIOC->ODR ^= GPIO_ODR_OD13;	// dbg led
}

void TIM2Config(void)
{
	// enable Timer 2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// make sure TIM2 is turned off
	TIM2->CR1 &= ~TIM_CR1_CEN;
	// enable ARR preload
	TIM2->CR1 |= TIM_CR1_ARPE;
	// timer clocked @ 48MHz
	TIM2->PSC = 48000;	// set prescaler to 4800 --> count @ 1kHz (every ms)
	TIM2->ARR = 1000;	// each step @ 1Hz (every s)

	// enable capture/compare channel 2 interrupt
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM2_IRQn, 0x03);
	NVIC_EnableIRQ(TIM2_IRQn);

	// reinintialze counter
	TIM2->EGR |= TIM_EGR_UG;

	// counter enable
	TIM2->CR1 |= TIM_CR1_CEN;
}