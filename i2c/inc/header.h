#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "stm32f411xe.h"
#include "rda5807.h"

#define		RETURN_SUCCESS				0x0
#define		RETURN_ERROR_BASE			0x80000000

#define		RETURN_ERROR_RCC_BASE			RETURN_ERROR_BASE + 0x000
#define 	RETURN_ERROR_GPIO_BASE			RETURN_ERROR_BASE + 0x100
#define		RETURN_ERROR_USART_BASE			RETURN_ERROR_BASE + 0x200
#define		RETURN_ERROR_I2C_BASE			RETURN_ERROR_BASE + 0x300
#define		RETURN_ERROR_RDA_BASE			RETURN_ERROR_BASE + 0x400

// I2C Error definitions
#define		RETURN_ERROR_I2C_NACK			RETURN_ERROR_I2C_BASE + 0x00
#define		RETURN_ERROR_I2C_ARLO			RETURN_ERROR_I2C_BASE + 0x01
#define		RETURN_ERROR_I2C_BERR			RETURN_ERROR_I2C_BASE + 0x02
#define		RETURN_ERROR_I2C_MSL			RETURN_ERROR_I2C_BASE + 0x03

// RDA Error definitions
#define		RETURN_ERROR_RDA_INVAL_CHIP_ID		RETURN_ERROR_RDA_BASE + 0x00
#define		RETURN_ERROR_RDA_INIT_FAILED		RETURN_ERROR_RDA_BASE + 0x01
#define		RETURN_ERROR_RDA_REGISTER_SET		RETURN_ERROR_RDA_BASE + 0x02
#define		RETURN_ERROR_RDA_REGISTER_GET		RETURN_ERROR_RDA_BASE + 0x03
#define		RETURN_ERROR_RDA_SEEK_TUNE_FAILED	RETURN_ERROR_RDA_BASE + 0x04


// pin definitons for I2C interface
#define I2C1_SCL    GPIO_ODR_OD6    // PB6
#define I2C1_SDA    GPIO_ODR_OD7    // PB7

// pin definitions for debug led
#define DBG_LED     GPIO_ODR_OD13

void rcc_config(void);
void gpio_config(void);
void usart_config(void);
void i2c1_config(void);

void usart_transmit_byte(uint8_t byte);
uint8_t usart_receive_byte(void);
void usart_transmit_hex(uint32_t hex);
void usart_transmit_string(const char *buf);
void usart_receive_string(char *buf, uint32_t len);

int32_t i2c1_transmit_byte(uint8_t addr, uint8_t byte);
int32_t i2c1_receive_byte(uint8_t addr, uint8_t *byte);
int32_t i2c1_transmit_bytes(uint8_t addr, uint8_t *buf, uint32_t len);
int32_t i2c1_receive_bytes(uint8_t addr, uint8_t *buf, uint32_t len);
const char *i2c_err_to_name(uint32_t err);

#endif // HEADER_H_INCLUDED
