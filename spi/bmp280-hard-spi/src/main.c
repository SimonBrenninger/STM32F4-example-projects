#include "header.h"

void sleep(volatile uint32_t delay)
{
	while(delay--);
}

int main(void)
{
	uint8_t data;
	uint32_t temp;

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
	SPI1_BMP280_set_ctrl_meas(0b00, 0b000, 0b001);

	// IIR filter off (filter[2:0])
	SPI1_BMP280_set_config(0b0, 0b000, 0b000);

	while(1)
	{
		// force single measurement with mode[1:0] = 0b01 / 0b10
		// osrs_p = x0 (0b000); osrs_t = x1 (0b001)
		SPI1_BMP280_set_ctrl_meas(0b01, 0b000, 0b001);

		// wait until measuring and im_update are cleared
		// (bit 3 & 0 of status register 0xF3)
		while(SPI1_BMP280_is_busy());

		// burst readout (start @ address 0xF7 up to 0xFC)
		temp = SPI1_BMP280_get_temp(16);

		USART1_SendDec(temp);
		USART1_SendString("\r\n\n");

		while(1);
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