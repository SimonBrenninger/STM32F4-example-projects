#include "header.h"

void gpio_config(void)
{
	/* configure UART1 pins PA9 (TX) and PA10 (RX) */
	// set mode for PA9 & PA10 to alternate function (AF) mode (0b10)
	GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk | GPIO_MODER_MODE10_Msk);
	GPIOA->MODER |= (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1);
	// set PA9 & PA10 to AF07
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9_Msk | GPIO_AFRH_AFSEL10_Msk);
	GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_0);
	GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL10_2 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_0);

	/* configure I2C1 pins PB6 (SCL) and PB7 (SDA) */
	// set mode for PB6 & PB7 to alternate function (AF) mode (0b10)
	GPIOB->MODER &= ~(GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);
	GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
	// set output type to open drain (0b1)
	GPIOB->OTYPER |= (GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);
	// enable pullup resistor for SCL & SDA (0b01 = pull up)
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6_Msk | GPIO_PUPDR_PUPD7_Msk);
	GPIOB->PUPDR |=  (GPIO_PUPDR_PUPD6_0 | GPIO_PUPDR_PUPD7_0);
	// set pin PB6 & PB7 to AF04
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_2;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_2;

	/* configure Debug LED PC13 */
	// set mode for PC13 to output mode (0b01)
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOC->MODER |= GPIO_MODER_MODE13_0;
	// clear Debug LED
	GPIOC->ODR |= DBG_LED;
}
