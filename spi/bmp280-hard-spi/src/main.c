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

	USART1_SendString("BMP280 hard-SPI Example\n\r");

	data = SPI1_BMP280_get_id();

	if(data == 0x58)
	{
		USART1_SendString("Read correct chip id\n\r");
	}
	else
	{
		USART1_SendString("Wrong chip id!\n\r");
	}

	while(1)
	{
		
	}
}

/*
 * Bugs resolved:
 * 
 * ToDo:
 * 
 */