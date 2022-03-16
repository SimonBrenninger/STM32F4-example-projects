#include "header.h"

void sleep(uint32_t delay)
{
	while(delay--);
}

int main(void)
{
	uint8_t data;

	RCCConfig();
	GPIOConfig();
	SPIConfig();
	USARTConfig();
	TIMConfig();

	USART1_SendString("BMP280 hard-SPI Example\r\n");

	data = SPI1_BMP280_get_id();

	USART1_SendString("0x");
	USART1_SendHex(data);
	USART1_SendString(": ");

	if(data == 0x58)
	{
		USART1_SendString("Read correct chip id\r\n\n");
	}
	else
	{
		USART1_SendString("Wrong chip id!\r\n\n");
	}

	while(1)
	{
		// do nothing
	}
}

/*
 * Bugs resolved:
 * SPI RX register would keep content received during first transmission
 * made it impossible to get information from sensor after first transmit
 * solution: clear OVR (overrun) bit after transmittion to overwrite RX content
 * 
 * ToDo:
 * 
 */