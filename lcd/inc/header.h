#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "stm32f411xe.h"
#include "lcd.h"

// pin definitions for debug led
#define DBG_LED GPIO_ODR_OD13

/*          global variables        */
typedef void (*timer_callback_t)(void);

/*            prototypes            */

// Configurations
void rcc_init(void);
void gpio_init(void);
void usart_init(void);
void timer_init(void);
void timer_register_callback(timer_callback_t callback);
void lcd_init(void);
void lcd_print_string(char *text);

// USART specific functions
char usart_rx(void);
void usart_tx(char c);
void usart_send_string(char *str, int len);
void usart_send_hex(uint8_t val);
void usart_send_dex(uint32_t val);
int _write(int handle, char* data, int len);

#endif // HEADER_H_INCLUDED
