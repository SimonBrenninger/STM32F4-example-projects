#include "header.h"

int main(void)
{
	SysClockConfig();
	GPIOConfig();
	TIM2Config();
	ADC1Config();

	// init starting levels of stepper
	// turn pin 3 & 1 off
	//GPIOA->ODR &= ~(STEPPER_PIN_3 | STEPPER_PIN_1);
	// turn pin 2 & 0 on
	//GPIOA->ODR |=  (STEPPER_PIN_2 | STEPPER_PIN_0);

	while(1)
	{

	}
}

/* 
 * Bugs resolved:
 * 
 * ToDo:
 * 
*/