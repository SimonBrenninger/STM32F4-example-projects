#include "header.h"

void SysClockConfig(void)
{
	// HSI = 16MHz
	// PLL out = 48MHz

	// reset prefetch and latency options of flash
	FLASH->ACR &= ~(0x10F);
	// set prefetch enable bit and flash latency to 1
	FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_1WS);

	// enable HSI
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));

	// reset PLL multiplication and source
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM_Msk
										 | RCC_PLLCFGR_PLLN_Msk
										 | RCC_PLLCFGR_PLLP_Msk);

	// select HSI as PLL input (=16MHz)
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
	// pll input clock division factor: 16MHz / 8 = 2MHz
	RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);
	// vco multiplication factor: 2MHz * 48 = 96MHz
	RCC->PLLCFGR |= (48 << RCC_PLLCFGR_PLLN_Pos);
	// main pll output division factor: 96MHz / 2 = 48MHz
	// 0b00 expands to division 2
	RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLP_Pos);

	// turn on PLL and wait for it to be ready
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	// select PLL as system clock source
	RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));

	// set AHB1 to sysclock
	RCC->CFGR &= ~RCC_CFGR_HPRE_DIV1;

	// set APB1 to AHB1 clock
	RCC->CFGR &= ~RCC_CFGR_PPRE1_DIV1;

	// set APB2 to AHB1 clock
	RCC->CFGR &= ~RCC_CFGR_PPRE2_DIV1;
}