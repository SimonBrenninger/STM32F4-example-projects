#include "header.h"

void GPIOConfig(void)
{
	// enable GPIO clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// set the pin as output
	GPIOC->MODER |= (1 << 26);	//PC13 (bit25 high)
}