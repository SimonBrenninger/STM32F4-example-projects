#include "header.h"

/* BMP280 Soft-SPI:
 * SPI mode '00' & '11' supported (mode '00' is used)
 * ('00': clock idle = 0, sampling @ falling edge)
 * ('11': clock idle = 1, sampling @ rising edge)
 * SPI 3 & 4-wire (using 4-wire configuration)
 * 
 */

void SPIConfig(void)
{
    // set CS pin high (disable SPI device BMP280)
    GPIOA->ODR |= SPI_CS;
    // set clock idle state to 0 (CPOL = 0)
    GPIOA->ODR &= ~SPI_SCK;
    // set MOSI state to 0
    GPIOA->ODR &= ~SPI_MOSI;
}

void sspi_write_byte(uint8_t byte)
{
    volatile uint8_t idx;
    // loop through byte bitwise (start with MSB)
    for(idx = 0x80; idx > 0x00; idx >>= 1)
    {
        // begin transmittion by setting SPI clock high
        GPIOA->ODR |= SPI_SCK;

        // dbg
        sleep(500);

        // transmit current bit
        if(byte & idx)
            GPIOA->ODR |=  SPI_MOSI;
        else
            GPIOA->ODR &= ~SPI_MOSI;
        
        // dbg
        sleep(500);

        // set SPI clock low again
        GPIOA->ODR &= ~SPI_SCK;

        // dbg
        sleep(1000);
    }
}

uint8_t sspi_read_byte(void)
{
    uint8_t idx, byte = 0x00;
    // loop through byte bitwise (start with MSB)
    for(idx = 0x80; idx > 0x00; idx >>= 1)
    {
        // begin reception by setting SPI clock high
        GPIOA->ODR |= SPI_SCK;

        // dbg
        sleep(1000);

        // set SPI clock low again
        GPIOA->ODR &= ~SPI_SCK;

        // dbg
        sleep(500);

        // get current MISO pin state and set corresponding bit
        if(GPIOA->IDR & SPI_MISO)
            byte |= idx;
        else
            byte &= ~idx;

        // dbg
        sleep(500);
    }
    return byte;
}