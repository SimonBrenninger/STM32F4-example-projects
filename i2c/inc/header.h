#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "stm32f411xe.h"

// pin definitons for I2C interface
#define I2C1_SCL    GPIO_ODR_OD6    // PB6
#define I2C1_SDA    GPIO_ODR_OD7    // PB7

// pin definitions for debug led
#define DBG_LED     GPIO_ODR_OD13

void RCCConfig(void);
void GPIOConfig(void);
void USARTConfig(void);
void I2C1Config(void);
void I2C1_start(void);
void I2C1_stop(void);

#endif // HEADER_H_INCLUDED