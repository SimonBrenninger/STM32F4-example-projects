#include "header.h"

void sleep(volatile uint32_t ms)
{
	ms *= 4;	// convert to ms
	while(ms--);
}

int main(void)
{
	RCCConfig();
	GPIOConfig();
	SPIConfig();
	USARTConfig();

	USART1_SendString("Hello World\n\r");

	uint8_t adr = 0x00, ret;

	GPIOC->ODR |= DBG_LED;

	while(1)
	{
		// read temp and pressure periodically

		// read from register 0xD0 (MSB 'RW' to '0' for reading)
		adr |=  0xD0;	// set register address
		adr &= ~0x80;	// set MSB to zero (read from device)

		sleep(4000);

		// start SPI communication
		GPIOA->ODR &= ~SPI_CS;

		sleep(1000);

		// write to SPI device
		sspi_write_byte(adr);

		sleep(500);
		GPIOC->ODR &= ~DBG_LED;
		sleep(500);

		// read content of address 0xD0
		ret = sspi_read_byte();

		sleep(500);
		GPIOC->ODR |= DBG_LED;
		sleep(500);

		// end SPI communication
		GPIOA->ODR |= SPI_CS;

		// send content of 0xD0 over USART
		USART1_SendString("Read from BMP280: content of 0xD0 is: 0x");
		USART1_SendHex(ret);
		USART1_SendString("\n\r");
		
		sleep(2000);
	}
}

/*
 * Bugs resolved:
 * sleep: compiler optimized sleep function into endless loop
 * sspi_write_byte: condition in for loop never met
 * 
 * ToDo:
 * correct GPIO speed
 * testing
 */