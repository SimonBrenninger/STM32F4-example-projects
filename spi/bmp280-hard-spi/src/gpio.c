#include "header.h"

void GPIOConfig(void)
{
	// enable GPIOA and GPIOC clock (25MHz)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	// configure SPI1 pins (CS: PA3, SCK: PA5, MISO: PA6, MOSI: PA7)

	// configure SPI1 pins in AF Mode (0b10); PA3 in output mode (0b01)
	GPIOA->MODER &= ~(GPIO_MODER_MODER3_Msk | 
					  GPIO_MODER_MODER5_Msk |
					  GPIO_MODER_MODER6_Msk | 
					  GPIO_MODER_MODER7_Msk);

	GPIOA->MODER |= (GPIO_MODER_MODER3_0 | 
					 GPIO_MODER_MODER5_1 | 
					 GPIO_MODER_MODER6_1 | 
					 GPIO_MODER_MODER7_1);
	
	// set CS pin high
	GPIOA->ODR |= SPI1_CS;

	// set GPIO pins to High Speed
	GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3_Msk | 
					   GPIO_OSPEEDR_OSPEED5_Msk | 
					   GPIO_OSPEEDR_OSPEED6_Msk | 
					   GPIO_OSPEEDR_OSPEED7_Msk);
	
	// set SPI1 pins to AF05
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL5_Msk | 
					   GPIO_AFRL_AFSEL6_Msk | 
					   GPIO_AFRL_AFSEL7_Msk);
	
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL5_Pos);
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL6_Pos);
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL7_Pos);

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