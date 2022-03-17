#include "header.h"

void SPI1_BMP280_start(void)
{
    // begin SPI1 communication by setting CS low
    GPIOA->ODR &= ~SPI1_CS;
}

void SPI1_BMP280_end(void)
{
    // end SPI1 communication by setting CS high
    GPIOA->ODR |= SPI1_CS;
}

uint8_t SPI1_BMP280_read_byte(uint8_t addr)
{
    // begin SPI1 communication
    SPI1_BMP280_start();
    addr = SPI1_read_byte(addr);
    // end SPI BMP280 communication
    SPI1_BMP280_end();
    return addr;
}

uint8_t *SPI1_BMP280_read_bytes(uint8_t addr, uint8_t num_bytes)
{
    uint8_t *bytes_ptr = NULL;
    // begin SPI1 communication
    SPI1_BMP280_start();
    bytes_ptr = SPI1_read_bytes(addr, num_bytes);
    // end SPI BMP280 communication
    SPI1_BMP280_end();
    return bytes_ptr;
}
void SPI1_BMP280_write_byte(uint8_t addr, uint8_t data)
{
    // for writing to BMP280 register set MSB of addr low
    addr &= ~(0x1 << 0x7);
    // begin SPI1 communication
    SPI1_BMP280_start();
    SPI1_write_byte(addr, data);
    // end SPI BMP280 communication
    SPI1_BMP280_end();
}

uint8_t SPI1_BMP280_get_id(void)
{
    uint8_t chip_id;

    // get result from BMP280 sensor
    chip_id = SPI1_BMP280_read_byte(BMP280_ID);

    // return value
    return chip_id;
}

void SPI1_BMP280_set_ctrl_meas(uint8_t mode, uint8_t osrs_p, uint8_t osrs_t)
{
    uint8_t temp = 0;
    temp |= osrs_t;
    temp <<= 0x3;
    temp |= osrs_p;
    temp <<= 0x2;
    temp |= mode;

    // write temp to BMP280
    SPI1_BMP280_write_byte(BMP280_CTRL_MEAS, temp);
}

void SPI1_BMP280_set_config(uint8_t spi3w_en, uint8_t filter, uint8_t t_sb)
{
    uint8_t temp = 0;
    temp |= t_sb;
    temp <<= 0x3;
    temp |= filter;
    temp <<= 0x2;
    temp |= spi3w_en;
    
    // write temp to BMP280
    SPI1_BMP280_write_byte(BMP280_CONFIG, temp);
}

void SPI1_BMP280_reset(void)
{
    // reset BMP280
    SPI1_BMP280_write_byte(BMP280_RESET, BMP280_RESET_VAL);
    // wait until BMP280 is ready
    while(SPI1_BMP280_read_byte(BMP280_STATUS) & BMP280_STATUS_IM_UPDATE);
}

void SPI1_BMP280_get_data(void)
{
    // start SPI communication
    SPI1_BMP280_start();

    SPI1_BMP280_get_temp(16);
    SPI1_BMP280_get_press(16);

    // end SPI communication
    SPI1_BMP280_end();

    // use calibration data to compute correct values

    USART1_SendString("current temperature is: \n\r");
}

uint32_t SPI1_BMP280_get_temp(uint8_t digits)
{
    uint32_t temp = 0;
    uint8_t *temp_ptr = NULL;

    // get temperature using burst readout (read from 0xFA to 0xFC at once)
    // receive 3 bytes (msb, lsb & xlsb) starting with 0xFA (MSB)
    temp_ptr = SPI1_BMP280_read_bytes(BMP280_TEMP_BASE, 3);

    // concatenate temp-pointer into one single temperature variable
    // copy msb and lsb to temp variable
    temp |= temp_ptr[0];
    temp <<= 8;
    temp |= temp_ptr[1];
    temp <<= 8;

    // use xlsb byte if 'digits' is greater than 16
    if(digits > 16)
    {
        // copy xlsb to temp variable
        temp |= temp_ptr[2];
        // since xslb bits start at bit 4 shift right 4 times
        temp >>= 4;
        // 'remove' digits from temp variable that are missing from 20 bits
        temp >>= (20 - digits);
    }

    // free memory allocated to temp_ptr
    free(temp_ptr);
    temp_ptr = NULL;
    return 0;
}

uint32_t SPI1_BMP280_get_press(uint8_t digits)
{
    //uint8_t *press_ptr = NULL;

    // get pressure using burst readout (read from 0xF7 to 0xF9 at once)
    // receive 3 bytes (msb, lsb & xlsb) starting with 0xF7 (MSB)
    //press_ptr = SPI1_BMP280_read_bytes(BMP280_PRESS_BASE, 3);
    return 0;
}