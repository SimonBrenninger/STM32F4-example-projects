#include <inttypes.h>
#include <stdbool.h>
#include "header.h"

// pin definitons for LCD interface
#define LCD_RS	GPIO_ODR_OD4  // PA4
#define LCD_EN	GPIO_ODR_OD5  // PA5
#define LCD_D0	GPIO_IDR_ID0  // PA0
#define LCD_D1	GPIO_ODR_OD1  // PA1
#define LCD_D2	GPIO_IDR_ID2  // PA2
#define LCD_D3	GPIO_ODR_OD3  // PA3

#define LCD_INSTR_CLEAR_DISPLAY			0x01
#define LCD_INSTR_RETURN_HOME 			0x02
#define LCD_INSTR_ENTRY_MODE			0x04
#define LCD_INSTR_DISPLAY_ON_OFF		0x08
#define LCD_INSTR_CURSOR_DISPLAY_SHIFT		0x10
#define LCD_INSTR_FUNCTION_SET			0x20
#define LCD_INSTR_SET_CGRAM_ADDRESS		0x40
#define LCD_INSTR_SET_DDRAM_ADDRESS		0x80
#define LCD_INSTR_WRITE_TO_DDRAM		0x80

#define RS_REGISTER	0
#define RS_DATA		1


static bool elapsed_40us = false;

static void timer_40us_callback(void)
{
	elapsed_40us = true;
}

static void wait_for_40us(uint32_t num_40us)
{
	if (num_40us == 0)
	{
		return;
	}
	uint32_t count_40us = 0;
	elapsed_40us = false;
	while (count_40us < num_40us)
	{
		if (elapsed_40us)
		{
			count_40us++;
		}
	}
}

static void lcd_send_nibble(uint8_t instr, uint8_t register_select)
{
	uint8_t nibble = instr & 0x0F;
	if (register_select == RS_REGISTER)
	{
		GPIOA->ODR &= ~LCD_RS;
	}
	else
	{
		GPIOA->ODR |= LCD_RS;
	}
	GPIOA->ODR &= ~(LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3);
	GPIOA->ODR |= nibble;
	GPIOA->ODR |= LCD_EN;
	wait_for_40us(1);
	GPIOA->ODR &= ~LCD_EN;
	wait_for_40us(1);
}

static void lcd_send_byte(uint8_t instr, uint8_t register_select)
{
	uint8_t nibble_instr = (instr & 0xF0) >> 4;
	lcd_send_nibble(nibble_instr, register_select);
	nibble_instr = instr & 0x0F;
	lcd_send_nibble(nibble_instr, register_select);
}

void lcd_clear_display(void)
{
	uint8_t instr = LCD_INSTR_CLEAR_DISPLAY;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_return_home(void)
{
	uint8_t instr = LCD_INSTR_RETURN_HOME;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(4); // wait at least for 1.52 ms
}

void lcd_set_cursor_direction(uint8_t enable, uint8_t direction)
{
	uint8_t instr = LCD_INSTR_ENTRY_MODE | enable | direction;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_display_control(uint8_t enable_display, uint8_t enable_cursor, uint8_t enable_blinking) 
{
	uint8_t instr = LCD_INSTR_DISPLAY_ON_OFF | enable_display | enable_cursor | enable_blinking;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_config_shift_mode(uint8_t shift_display_cursor, uint8_t direction) 
{
	uint8_t instr = LCD_INSTR_CURSOR_DISPLAY_SHIFT | shift_display_cursor | direction;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_set_function(uint8_t data_length, uint8_t number_of_lines, uint8_t font)
{
	uint8_t instr = LCD_INSTR_FUNCTION_SET | data_length | number_of_lines | font;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_set_cursor_position(uint8_t position)
{
	position &= 0x7F;
	uint8_t instr = LCD_INSTR_SET_DDRAM_ADDRESS | position;
	lcd_send_byte(instr, RS_REGISTER);
	wait_for_40us(1);
}

void lcd_print_character(uint8_t c) 
{
	lcd_send_byte(c, RS_DATA);
	wait_for_40us(1);
}

void lcd_init(void)
{
	timer_register_callback(timer_40us_callback);
	// wait for power on of lcd screen (40ms)
	wait_for_40us(10000);
	// send nibble (set function bit 4-7)
	lcd_send_nibble(0x02, RS_REGISTER);
	wait_for_40us(1);
	lcd_set_function(LCD_FUNCTION_SET_DATA_LENGTH_4_BIT, 
			 LCD_FUNCTION_SET_2_LINES, 
			 LCD_FUNCTION_SET_FONT_5x8);
	lcd_display_control(LCD_DISPLAY_ENABLE, LCD_DISPLAY_CURSOR_ENABLE, LCD_DISPLAY_CURSOR_BLINK);
	lcd_set_cursor_direction(LCD_ENTRY_MODE_INC_DEC_DISABLE, LCD_ENTRY_MODE_INCREMENT);
}


void lcd_print_string(char *text)
{
	int i = 0;
	while (text[i] != '\0')
	{
		lcd_print_character(text[i]);
		i++;
	}
}
