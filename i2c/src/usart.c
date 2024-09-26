#include "header.h"

int _write(int handle, char* data, int len)
{
	usart_transmit_string(data);
	return len;
}

void usart_transmit_byte(uint8_t byte)
{
	// wait until transmit data register is empty
	while (!(USART1->SR & USART_SR_TXE));
	USART1->DR = byte;
	// wait until transmission has conpleted
	while (!(USART1->SR & USART_SR_TC));
}

uint8_t usart_receive_byte(void)
{
	// wait until reception data register is not empty
	while (!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;
}

void usart_transmit_hex(uint32_t hex)
{
	uint8_t nibble;
	int8_t nibble_idx = 7;
	const uint8_t nibble_size = 4;
	usart_transmit_string("0x");
	while (nibble_idx >= 0)
	{
		nibble = hex >> (nibble_idx * nibble_size);
		nibble &= 0x0F;
		if (nibble >= 0x0A)
		{
			usart_transmit_byte('A' + (nibble-0x0A));
		}
		else
		{
			usart_transmit_byte('0' + nibble);
		}
		nibble_idx--;
	}
}

void usart_transmit_string(const char *buf)
{
	uint32_t i = 0;
	while (buf[i] != '\0')
	{
		usart_transmit_byte(buf[i++]);
	}
}

void usart_receive_string(char *buf, uint32_t len)
{
	uint32_t i = 0;
	while (i < len)
	{
		buf[i++] = usart_receive_byte();
	}
}

void usart_config(void)
{
	// enable USART CR = 1
	USART1->CR1 |= USART_CR1_UE;
	// select baud rate
	// baud = f_ck / (8 * (2-OVER8) * USARTDIV)
	// USARTDIV = f_ck / (8 * (2-OVER8) * baud)
	// for f_ck = 25MHz, OVER8 = 0, baud = 115200:
	// USARTDIV = 13.563
	// -> Mantissa = 13 = 0x0D
	// -> Fraction = 16 * .563 = 9.01 ~ 0x09
	USART1->BRR &= ~(USART_BRR_DIV_Mantissa_Msk | USART_BRR_DIV_Fraction_Msk);
	USART1->BRR |= (0x0D << USART_BRR_DIV_Mantissa_Pos);
	USART1->BRR |= (0x09 << USART_BRR_DIV_Fraction_Pos);
	// set TE bit (to send an idle frame)
	// set RE bit
	USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);
}

/* transmission */
// write data to DR register
// wait until TC = 1

/* reception */
// once data in RDR is available: RXNE is set
