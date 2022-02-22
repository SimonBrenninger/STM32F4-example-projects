#include <stm32f411xe.h>

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define PWM_STEPS 200

void SysClockConfig(void);
void TIM2Config(void);
void GPIOConfig(void);

#endif // HEADER_H_INLCUDED