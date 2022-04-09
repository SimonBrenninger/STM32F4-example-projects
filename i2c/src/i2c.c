#include "header.h"

/* RDA5807 Interface Timing Characteristics
 * f_max = 400kHz
 * T_rise_scl_max = 300ns
 * 
 * adress: (0010000b)
 */

/*
 * periph input clock: CR2
 * clock control register
 * rise time register
 * enable periph: CR1
 * start condition with START bit in CR1
 */

void I2C1Config(void)
{
    // enable I2C1 periph clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // set periph input clock (APB1 = 25MHz) into CR2
    I2C1->CR2 |= (25 << I2C_CR2_FREQ_Pos);
    // set SCL clock frequency to 100kHz (=0.01ms = 10us)
    // T_scl/2 = CCR * T_pclk1
    // 10us / 2 = CCR * (1 / 25MHz)
    // CCR = 5us * 25MHz = 125
    // CCR = 125
    I2C1->CCR |= (125 << I2C_CCR_CCR_Pos);
    // set rise time
    // t_rise_scl_max / T_pclk1 + 1
    // 300ns / (1 / 25MHz) + 1
    // 300ns * 25MHz + 1 = 8.5 --> 8
    I2C1->TRISE = 8;
    
    // enable I2C1 peripheral
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_start(void)
{
    // send start condition
    I2C1->CR1 |= I2C_CR1_START;
}

void I2C1_stop(void)
{
    // send stop condition
    I2C1->CR1 |= I2C_CR1_STOP;
}