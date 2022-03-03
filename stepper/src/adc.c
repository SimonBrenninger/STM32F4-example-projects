#include "header.h"

void ADC_IRQHandler()
{
    if(ADC1->CR1 & ADC_CR1_EOCIE)
    {
        ADC1->CR1 &= ~ADC_CR1_EOCIE;
    }
    // map ADC conversion value to TIM2 ARR register
    // ADC output: 0x000...0xFFF, ARR: 20...1000 (20-1000ms)
    // ARR = (0..1023)-20 = 0x000...0x3FF
    // ARR = ADC->DR * 0x3FF / 0xFFF -20

    TIM2->ARR = (ADC1->DR * 0x3FF / 0xFFF - 20);
}

void ADC1Config(void)
{
    // f_ADC max: 18MHz

    // enable ADC1 peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // set adc prescaler to /4 (48MHz / 4 = 12MHz)
    ADC1_COMMON->CCR &= ~ADC_CCR_ADCPRE_Msk;
    ADC1_COMMON->CCR |=  ADC_CCR_ADCPRE_0;

    // enable end-of-conversion interrupt
    ADC1->CR1 |= ADC_CR1_EOCIE;

    // disable continuos mode
    ADC1->CR2 &= ~ADC_CR2_CONT;

    // set interrupt priority and enable ISR
    NVIC_SetPriority(ADC_IRQn, 0x04);
    NVIC_EnableIRQ(ADC_IRQn);

    // turn on ADC1 peripheral
    ADC1->CR2 |= ADC_CR2_ADON;

    // start ADC1 single conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
}