#include "header.h"

void GPIOConfig(void)
{
	// configure USART1 pins (TX: PA9 & RX: PA10) in AF Mode
	// enable GPIOA clock (100MHz)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/*		configure PA9 (TX)		*/
	// set pin PA9 mode to AF (0b10)
	GPIOA->MODER &= ~GPIO_MODER_MODER9_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER9_1;
	// set pin PA9 to AF07 (USART1_TX)
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL9_Msk;
	GPIOA->AFR[1] |=  (0x7 << GPIO_AFRH_AFSEL9_Pos);

	/*		configure PA10 (RX)		*/
	// set pin PA10 mode to AF (0b10)
	GPIOA->MODER &= ~GPIO_MODER_MODE10_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER10_1;
	// set pin PA10 to AF07 (USART1_RX)
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL10_Msk;
	GPIOA->AFR[1] |=  (0x7 << GPIO_AFRH_AFSEL10_Pos);

	// configure dbg led
	GPIOC->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOC->MODER |=  GPIO_MODER_MODE13_0;

	// turn off led on PC13
    GPIOC->ODR |= GPIO_ODR_OD13;
}