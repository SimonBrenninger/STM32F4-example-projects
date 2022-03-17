#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include "stm32f411xe.h"
#include "bmp280.h"

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
uint8_t SPI1_transceive(uint8_t byte);
uint8_t SPI1_read_byte(uint8_t addr);
uint8_t *SPI1_read_bytes(uint8_t addr, uint8_t num_bytes);
void SPI1_write_byte(uint8_t addr, uint8_t data);

// BMP280 specific functions
void SPI1_BMP280_start(void);
void SPI1_BMP280_end(void);
uint8_t SPI1_BMP280_read_byte(uint8_t addr);
uint8_t *SPI1_BMP280_read_bytes(uint8_t addr, uint8_t num_bytes);
void SPI1_BMP280_write_byte(uint8_t addr, uint8_t data);
uint8_t SPI1_BMP280_get_id(void);
void SPI1_BMP280_set_ctrl_meas(uint8_t mode, uint8_t osrs_p, uint8_t osrs_t);
void SPI1_BMP280_set_config(uint8_t spi3w_en, uint8_t filter, uint8_t t_sb);
void SPI1_BMP280_reset(void);
uint8_t SPI1_BMP280_is_busy(void);
void SPI1_BMP280_get_data(void);
uint32_t SPI1_BMP280_get_temp(uint8_t digits);
uint32_t SPI1_BMP280_get_press(uint8_t digits);

// USART specific functions
char USART1_RX(void);
void USART1_TX(char c);
void USART1_SendString(char *str);
void USART1_SendHex(uint8_t val);
void USART1_SendDec(uint32_t val);

#endif // HEADER_H_INCLUDED