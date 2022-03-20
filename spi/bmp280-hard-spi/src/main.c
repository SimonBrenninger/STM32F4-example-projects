#include "header.h"

uint8_t interval_passed = 0;

int main(void)
{
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
    

    printf("BMP280 hard-SPI Example\r\n");

    if(SPI1_BMP280_read_byte(BMP280_ID) == BMP280_ID_VAL)
    {
        printf("Read correct chip id\r\n\n");
    }
    else
    {
        printf("Wrong chip id!\r\n\n");
    }

    // get calibration data
    SPI1_BMP280_get_calib(&bmp280_conf, &bmp280_calib);

    while(1)
    {
        if(interval_passed)
        {
            interval_passed = 0;
            // start next temp & pressure measurement
            
            // start measurement of BMP280
            SPI1_BMP280_config(&bmp280_conf);
            
            // get raw data
            SPI1_BMP280_get_raw(&bmp280_raw);

            // compute temperature
            temp = BMP280_compute_temp(&bmp280_calib, &bmp280_raw);

            // compute pressure
            press = BMP280_compute_press(&bmp280_calib, &bmp280_raw);
            
            printf("raw pressure: %"PRIu32"\r\n", bmp280_raw.press);
            printf("raw temperature: %"PRIu32"\r\n", bmp280_raw.temp);
            
            printf("real pressure: %"PRIu32"hPa\r\n", press/2650);
            printf("real temperature: %"PRIu32"°C\r\n\n\n", temp);
        }
    }
}

/*
 * Bugs resolved:
 * SPI RX register would keep content received during first transmission
 * made it impossible to get information from sensor after first transmit
 * solution: clear OVR (overrun) bit after transmittion to overwrite RX content
 * 
 * ToDo:
 * convert float into two integers to send values over UART1
 */