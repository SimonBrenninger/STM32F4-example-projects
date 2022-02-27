#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "stm32f411xe.h"

// pin definitons for SPI interface
#define SPI_SCK  GPIO_ODR_OD0
#define SPI_MOSI GPIO_ODR_OD1
#define SPI_MISO GPIO_IDR_ID2
#define SPI_CS   GPIO_ODR_OD3

// pin definitions for debug led
#define DBG_LED GPIO_ODR_OD13

void RCCConfig(void);
void GPIOConfig(void);
void USARTConfig(void);
void SPIConfig(void);
char USART1_RX(void);
void USART1_TX(char c);
void USART1_SendString(char *str);
void USART1_SendHex(uint8_t val);
void sspi_write_byte(uint8_t byte);
uint8_t sspi_read_byte(void);
void sleep(volatile uint32_t ms);

#endif // HEADER_H_INCLUDED