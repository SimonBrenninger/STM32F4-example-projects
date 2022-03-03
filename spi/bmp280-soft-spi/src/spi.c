#include "header.h"

/* BMP280 Soft-SPI:
 * SPI mode '00' & '11' supported (mode '00' is used)
 * ('00': clock idle = 0, sampling @ rising edge)
 * ('11': clock idle = 1, sampling @ falling edge)
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
    // CPHA = '0' -> transmit @ falling edge & sample @ rising edge
    for(idx = 0x80; idx > 0x00; idx >>= 1)
    {
        // SCK still low -> transmit current bit
        if(byte & idx)
            GPIOA->ODR |=  SPI_MOSI;
        else
            GPIOA->ODR &= ~SPI_MOSI;
        
        // dbg
        sleep(2);

        // set SPI clock high
        GPIOA->ODR |= SPI_SCK;

        // dbg
        sleep(2);

        // set SPI clock low again
        GPIOA->ODR &= ~SPI_SCK;
    }
}

uint8_t sspi_read_byte(void)
{
    uint8_t idx, byte = 0x00;

    GPIOC->ODR &= ~DBG_LED;

    // loop through byte bitwise (start with MSB)
    // CPHA = '0' -> sample @ falling edge
    for(idx = 0x80; idx > 0x00; idx >>= 1)
    {
        // dbg
        sleep(2);

        // begin reception by setting SPI clock high
        GPIOA->ODR |= SPI_SCK;

        // dbg
        sleep(2);

        // set SPI clock low again
        GPIOA->ODR &= ~SPI_SCK;

        // get current MISO pin state and set corresponding bit
        if(GPIOA->IDR & SPI_MISO)
            byte |= idx;
        else
            byte &= ~idx;
    }

    GPIOC->ODR |= DBG_LED;

    return byte;
}