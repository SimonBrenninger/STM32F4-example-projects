#include "header.h"

void gpio_init(void)
{
	// enable GPIOA and GPIOC clock (25MHz)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

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


	// configure LCD Pins (RS: PA4, EN: PA5, D4: PA0, D5: PA1, D6: PA2, D7: PA3)
	// set pin PA4 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE4_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER4_0;

	// set pin PA5 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER5_0;
	
	// set pin PA0 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER0_0;

	// set pin PA1 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER1_0;

	// set pin PA2 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER2_0;

	// set pin PA3 mode to output (0b01)
	GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODER3_0;


	// configure User led (Pc13)
	// configure dbg led
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOC->MODER |=  GPIO_MODER_MODE13_0;

	// turn off led on PC13
	GPIOC->ODR |= DBG_LED;
}
