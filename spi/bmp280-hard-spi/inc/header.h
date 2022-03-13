#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include "stm32f411xe.h"

// pin definitons for SPI interface
#define SPI1_CS   GPIO_ODR_OD3  // PA3
#define SPI1_SCK  GPIO_ODR_OD5  // PA5
#define SPI1_MISO GPIO_IDR_ID6  // PA6
#define SPI1_MOSI GPIO_ODR_OD7  // PA7

// pin definitions for debug led
#define DBG_LED GPIO_ODR_OD13

/*          prototypes            */

// Configurations
void RCCConfig(void);
void GPIOConfig(void);
void SPIConfig(void);
void USARTConfig(void);
void TIMConfig(void);

// SPI specific functions
void SPI1_transmit(uint8_t byte);
uint8_t SPI1_receive(void);
uint8_t SPI1_read_byte(uint8_t addr);
uint8_t *SPI1_read_bytes(uint8_t addr, uint8_t num_bytes);
void SPI1_write_byte(uint8_t addr, uint8_t data);
uint8_t SPI1_BMP280_get_id(void);
void SPI1_BMP280_get_data(void);
uint32_t SPI1_BMP280_get_temp(void);
uint32_t SPI1_BMP280_get_press(void);
void SPI1_start_communication(void);
void SPI1_end_communication(void);

// USART specific functions
char USART1_RX(void);
void USART1_TX(char c);
void USART1_SendString(char *str);
void USART1_SendHex(uint8_t val);

#endif // HEADER_H_INCLUDED