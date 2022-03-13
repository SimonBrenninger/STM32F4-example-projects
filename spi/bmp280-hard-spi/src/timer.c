#include "header.h"

void TIM5_IRQHandler(void)
{
    if(TIM5->SR & TIM_SR_UIF)
    {
        TIM5->SR &= ~TIM_SR_UIF;
    }

    // start next temp & pressure measurement
    SPI1_BMP280_get_data();
}

void TIMConfig(void)
{
    // configure TIM5 to measure temperature
    // and pressure every 1 second

    TIM5->CR1 = 0x0;    // clock division to 1

    // set counter prescaler and auto-reload register
    TIM5->PSC = 25000-1;    // 25MHz / 25000 = 1kHz
    TIM5->ARR = 1000-1;     // 1kHz / 1000 = 1Hz -> INT every 1s

    // enable update interrupt
    TIM5->DIER |= TIM_DIER_UIE;

    // set nvic priority and enable interrupt handler
    NVIC_SetPriority(TIM5_IRQn, 57);
    NVIC_EnableIRQ(TIM5_IRQn);

    // enable timer 5 counter
    TIM5->CR1 |= TIM_CR1_CEN;
}