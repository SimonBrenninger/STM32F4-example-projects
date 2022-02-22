#include "header.h"

void RCCConfig(void)
{
    // set regulator voltage scaling output (0b11: <= 100MHz)
    PWR->CR |= (PWR_CR_VOS_1 | PWR_CR_VOS_0);

    // set flash wait states
    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
    FLASH->ACR |= (0x6 << FLASH_ACR_LATENCY_Pos);

    // use HSE and PLL
    // SysClock @ 100MHz

    /*      configure HSE       */
    // enable HSE clock (25MHz)
    RCC->CR |= RCC_CR_HSEON;
    // wait till HSE is ready
    while(!(RCC->CR & RCC_CR_HSERDY));

    /*      configure PLL       */
    // set PLL source to HSE
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    // set PLL factors
    // PLL_OUT = HSE / PLLM * PLLN / PLLP
    // 100MHz = 25MHz / 20 * 160 / 2
    // set PLLM factor (20 = 0x14)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
    RCC->PLLCFGR |=  (0x14 << RCC_PLLCFGR_PLLM_Pos);
    // set PLLN factor (160 = 0xA0)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
    RCC->PLLCFGR |=  (0xA0 << RCC_PLLCFGR_PLLN_Pos);
    // set PLLP factor (2 = 0x2, but PLLP=0 starts with division factor 2)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;
    RCC->PLLCFGR |=  (0x0 << RCC_PLLCFGR_PLLP_Pos);
    // enable PLL
    RCC->CR |= RCC_CR_PLLON;
    // wait till PLL is ready
    while(!(RCC->CR & RCC_CR_PLLRDY));

    // set SYSCLOCK source to PLL
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |=  RCC_CFGR_SW_PLL;
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));

    // set AHB clock to system clock (100MHz)
    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;

    // set APB2 (for USART1) to AHB clock (100MHz)
    RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
    RCC->CFGR |=  RCC_CFGR_PPRE2_DIV1;
}