#include "header.h"

void rcc_config(void)
{
	// use HSE & SysClock @ 25MHz

	/*      configure HSE       */
	// enable HSE clock (25MHz)
	RCC->CR |= RCC_CR_HSEON;
	// wait till HSE is ready
	while(!(RCC->CR & RCC_CR_HSERDY));

	// set SYSCLOCK source to HSE
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |=  RCC_CFGR_SW_HSE;
	// wait until HSE clock is ready
	while(!(RCC->CFGR & RCC_CFGR_SWS_HSE));

	// set AHB clock to system clock (25MHz)
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;

	// set APB1 (I2C1) to AHB clock (25MHz)
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |=  RCC_CFGR_PPRE1_DIV1;

	// set APB2 (for USART1) to AHB clock (25MHz)
	RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
	RCC->CFGR |=  RCC_CFGR_PPRE2_DIV1;

	// enable GPIOA, GPIOB and GPIOC clock
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

	// enable I2C1 clock
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	// enable USART1 clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
}
