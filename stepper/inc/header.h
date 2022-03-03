#include <stm32f411xe.h>

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define STEPPER_PIN_0 GPIO_ODR_OD0
#define STEPPER_PIN_1 GPIO_ODR_OD1
#define STEPPER_PIN_2 GPIO_ODR_OD2
#define STEPPER_PIN_3 GPIO_ODR_OD3

void SysClockConfig(void);
void GPIOConfig(void);
void TIM2Config(void);
void ADC1Config(void);

#endif // HEADER_H_INLCUDED