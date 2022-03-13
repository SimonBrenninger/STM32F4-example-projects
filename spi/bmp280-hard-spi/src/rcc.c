#include "header.h"

void RCCConfig(void)
{
    // use HSE
    // SysClock @ 25MHz

    /*      configure HSE       */
    // enable HSE clock (25MHz)
    RCC->CR |= RCC_CR_HSEON;
    // wait till HSE is ready
    while(!(RCC->CR & RCC_CR_HSERDY));

    // set SYSCLOCK source to HSE
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |=  RCC_CFGR_SW_HSE;
    while(!(RCC->CFGR & RCC_CFGR_SWS_HSE));

    // set AHB clock to system clock (25MHz)
    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;

    // set APB1 for (TIM5) to AHB clock (25MHz)
    RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
    RCC->CFGR |=  RCC_CFGR_PPRE1_DIV1;
    
    // set APB2 (for USART1, SPI1) to AHB clock (25MHz)
    RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
    RCC->CFGR |=  RCC_CFGR_PPRE2_DIV1;
}