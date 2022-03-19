#include "header.h"

uint8_t interval_passed = 0;

void sleep(volatile uint32_t delay)
{
	while(delay--);
}

int main(void)
{
	uint8_t data;
	// initialize bmp280 configuration structure
	struct bmp280_conf_t bmp280_conf = {
		.filter   = BMP280_FILTER_DISABLE,
		.mode     = BMP280_MODE_FORCED,
		.osrs_p   = BMP280_OSRS_P_SKIP,
		.osrs_t   = BMP280_OSRS_T_OSRS_1,
		.spi3w_en = BMP280_SPI3W_EN_DISABLE,
		.t_sb	  = BMP280_T_SB_0_5_MS
	};
	struct bmp280_calib_t bmp280_calib;
	struct bmp280_raw_t bmp280_raw;

	RCCConfig();
	GPIOConfig();
	SPIConfig();
	USARTConfig();
	TIMConfig();

	USART1_SendString("BMP280 hard-SPI Example\r\n");

	data = SPI1_BMP280_read_byte(BMP280_ID);

	if(data == BMP280_ID_VAL)
	{
		USART1_SendString("Read correct chip id\r\n\n");
	}
	else
	{
		USART1_SendString("Wrong chip id!\r\n\n");
	}

	// configure measurement of BMP280
	SPI1_BMP280_config(&bmp280_conf);

	while(1);
	{
		// start next temp & pressure measurement
		// burst readout (start @ address 0xF7 up to 0xFC)
		uint32_t temp = SPI1_BMP280_get_temp(16);

		USART1_SendDec(temp);
		USART1_SendString("\r\n\n");
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