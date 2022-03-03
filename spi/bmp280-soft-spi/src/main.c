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

	USART1_SendString("BMP280 soft-SPI Example\n\r");

	uint8_t adr = 0x00, ret;

	GPIOC->ODR |= DBG_LED;

	while(1)
	{
		// read from register 0xD0 (chip_id register)
		adr  = 0xD0;	// set register address
		adr |= 0x80;	// set MSB (R/W) to one (read from device)

		sleep(4000);

		// start SPI communication
		GPIOA->ODR &= ~SPI_CS;

		// write to SPI device
		sspi_write_byte(adr);

		// read content of address 0xD0 (for BMP280 always 0x58)
		ret = sspi_read_byte();

		// end SPI communication
		GPIOA->ODR |= SPI_CS;

		// send content of 0xD0 over USART
		USART1_SendString("Read from BMP280: content of 0xD0 (chip_id) is: 0x");
		USART1_SendHex(ret);
		USART1_SendString(" (normally 0x58)\n\r");
		
		sleep(2000);
	}
}

/*
 * Bugs resolved:
 * sleep: compiler optimized sleep function into endless loop
 * sspi_write_byte: condition in for loop never met
 * spi.c: used wrong SPI configuration (CPHA=1 instead of CPHA=0)
 * 
 * ToDo:
 */