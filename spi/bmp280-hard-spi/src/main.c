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

	if(data == BMP280_ID_VAL)
	{
		USART1_SendString("Read correct chip id\r\n\n");
	}
	else
	{
		USART1_SendString("Wrong chip id!\r\n\n");
	}

	// configure measurement of BMP280

	// oversampling = ultra low power
	// osrs_p = x0 (0b000); osrs_t = x1 (0b001)

	// IIR filter off (filter[2:0])

	while(1)
	{
		// force single measurement with mode[1:0] = 0b01 / 0b10

		// wait until measuring and im_update are cleared
		// (bit 3 & 0 of status register 0xF3)

		// burst readout (start @ address 0xF7 up to 0xFC)
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