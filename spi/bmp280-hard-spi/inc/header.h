#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "stm32f411xe.h"
#include "bmp280.h"

// pin definitons for SPI interface
#define SPI1_CS   GPIO_ODR_OD3  // PA3
#define SPI1_SCK  GPIO_ODR_OD5  // PA5
#define SPI1_MISO GPIO_IDR_ID6  // PA6
#define SPI1_MOSI GPIO_ODR_OD7  // PA7

// pin definitions for debug led
#define DBG_LED GPIO_ODR_OD13

/*          global variables        */
extern uint8_t interval_passed;

/*            prototypes            */

// Configurations
void RCCConfig(void);
void GPIOConfig(void);
void SPIConfig(void);
void USARTConfig(void);
void TIMConfig(void);

// SPI specific functions
uint8_t SPI1_transceive(uint8_t byte);
uint8_t SPI1_read_byte(uint8_t addr);
uint8_t *SPI1_read_bytes(uint8_t start_addr, uint8_t num_bytes);
void SPI1_write_byte(uint8_t addr, uint8_t data);
void SPI1_write_bytes(uint8_t start_addr, uint8_t *data_ptr, uint8_t num_bytes);

// USART specific functions
char USART1_RX(void);
void USART1_TX(char c);
void USART1_SendString(char *str, int len);
void USART1_SendHex(uint8_t val);
void USART1_SendDec(uint32_t val);
int _write(int handle, char* data, int len);

#endif // HEADER_H_INCLUDED