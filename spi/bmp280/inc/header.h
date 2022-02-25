#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "stm32f411xe.h"

void RCCConfig(void);
void GPIOConfig(void);
void USARTConfig(void);
void SPIConfig(void);
char USART1_RX(void);
void USART1_TX(char c);
void USART1_SendString(char *str);

#endif // HEADER_H_INCLUDED