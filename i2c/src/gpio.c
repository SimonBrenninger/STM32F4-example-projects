#include "header.h"

void GPIOConfig(void)
{
	// enable GPIOB and GPIOC periph clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    // set mode for debug led (PC13) to output mode (0b01)
    GPIOC->MODER |= GPIO_MODER_MODE13_0;
    // clear dbg led
    GPIOC->ODR |= DBG_LED;

    // set mode for SCL (PB6) & SDA (PB7) pins to alternate function (AF) mode (0b10)
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    // set pin PB6 & PB7 to AF04
    GPIOB->AFR[0] |= ((0x04 << GPIO_AFRL_AFSEL6_Pos) | (0x04 << GPIO_AFRL_AFSEL7_Pos));
}