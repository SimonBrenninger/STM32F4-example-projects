#include "header.h"

uint8_t interval_passed = 0;

void sleep(volatile uint32_t delay)
{
    while(delay--);
}

int main(void)
{
    uint8_t data;
    int32_t temp;
    uint32_t press;

    // initialize bmp280 configuration structure
    bmp280_conf_t bmp280_conf = {
        .filter   	= BMP280_FILTER_DISABLE,
        .mode     	= BMP280_MODE_FORCED,
        .osrs_press	= BMP280_OSRS_P_OSRS_1,
        .osrs_temp	= BMP280_OSRS_T_OSRS_1,
        .spi3w_en 	= BMP280_SPI3W_EN_DISABLE,
        .t_sb		= BMP280_T_SB_0_5_MS
    };
    bmp280_calib_t bmp280_calib;
    bmp280_raw_t bmp280_raw;

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

    // get calibration data
    SPI1_BMP280_get_calib(&bmp280_conf, &bmp280_calib);

    // get raw data
    SPI1_BMP280_get_raw(&bmp280_raw);
    
    USART1_SendString("raw pressure: ");
    USART1_SendDec(bmp280_raw.press);
    USART1_SendString("    raw temperature: ");
    USART1_SendDec(bmp280_raw.temp);

    // compute temperature
    temp = BMP280_compute_temp(&bmp280_calib, &bmp280_raw);

    // compute pressure
    press = BMP280_compute_press(&bmp280_calib, &bmp280_raw);

    USART1_SendString("    real pressure: ");
    USART1_SendDec(press/2650);
    USART1_SendString("    real temperature: ");
    USART1_SendDec(temp);
    USART1_SendString("\r\n");

    while(1);
    while(1)
    {
        // start next temp & pressure measurement
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