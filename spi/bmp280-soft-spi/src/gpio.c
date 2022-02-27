#include "header.h"

void GPIOConfig(void)
{
	// configure SPI pins (SCK: PA0, MOSI: PA1, MISO: PA2, CS: PA3)

	// enable GPIOA and GPIOC clock (195kHz)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	// set pin mode for PA0, PA1 & PA3 to GP output (0b01)
	// and PA2 (MISO) to input (0b00)
	GPIOA->MODER &= ~(GPIO_MODER_MODER0_Msk | 
					  GPIO_MODER_MODER1_Msk |
					  GPIO_MODER_MODER2_Msk | 
					  GPIO_MODER_MODER3_Msk);

	GPIOA->MODER |= (GPIO_MODER_MODER0_0 | 
					 GPIO_MODER_MODER1_0 | 
					 GPIO_MODER_MODER3_0);

	// configure USART1 pins (TX: PA9 & RX: PA10) in AF Mode

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
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOC->MODER |=  GPIO_MODER_MODE13_0;

	// turn off led on PC13
    GPIOC->ODR |= DBG_LED;
}