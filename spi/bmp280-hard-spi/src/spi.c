#include "header.h"

// BMP280 SPI-CS max frequency = 10MHz

void SPIConfig(void)
{
    // enable SPI1 peripheral clock (25MHz)
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // set DFF (data frame) to 8 bit
    SPI1->CR1 &= ~SPI_CR1_DFF;
    // set SPI mode to full-duplex
    SPI1->CR1 &= ~SPI_CR1_RXONLY;
    // set baud rate (SPI clock divider) to / 4 (6,25MHz) (0b001)
    SPI1->CR1 &= ~SPI_CR1_BR;
    SPI1->CR1 |=  SPI_CR1_BR_0;
    // set CPOL and CPHA to '0'
    SPI1->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);
    // set LSBFISRT to '0' (transmit MSB first)
    SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);
    // set SSM to '1' (software slave management; control CS/SS pin using software)
    SPI1->CR1 |= SPI_CR1_SSM;
    // set and reset the NSS pin using the SSI bit (start with SS = 1)
    SPI1->CR1 |= SPI_CR1_SSI;
    // set SPI1 mode to master (MSTR=1)
    SPI1->CR1 |= SPI_CR1_MSTR;

    SPI1->CR2 = 0x0;
    
    // enable SPI (SPE=1)
    SPI1->CR1 |= SPI_CR1_SPE;

    // check that SPI1 TX RX registers are empty
    // next time we don't need to wait
    // until the flag is cleared before sending/
    while(!(SPI1->SR & SPI_SR_TXE));
    while((SPI1->SR & SPI_SR_RXNE));
}

/* disabling the SPI peripheral:
 * wait until: RXNE = 1, TXE = 1, BSY = 0
 * disable SPI with SPE = 0 & disable SPI periph clock
*/

void SPI1_Transmit(uint8_t byte)
{
    // wait until previous transmition is finished (TX register empty)
    while(!(SPI1->SR & SPI_SR_TXE));

    // transmit byte via SPI
    SPI1->DR = byte;
}

uint8_t SPI1_Receive()
{
    uint8_t byte;

    // wait until SPI1 is not busy anymore
    while(SPI1->SR & SPI_SR_BSY);
    // send nonsense data during reception
    SPI1->DR = 0x0;
    // wait until transmition is finished (TX register empty)
    while(!(SPI1->SR & SPI_SR_TXE));

    // receive byte from SPI1
    byte = SPI1->DR;

    // return received byte
    return byte;
}

uint8_t SPI1_BMP280_get_id(void)
{
    // send command to transmit chip id (adress 0xD0)
    // MSB is used as R/W bit (W=0, R=1); for reading MSB can be left as is
    uint8_t chip_id =0xD0;

    // begin SPI1 communication
    SPI1_start_communication();

    SPI1_Transmit(0xD0);

    // get result from BMP280 sensor
    chip_id = SPI1_Receive();

    // end SPI1 communication
    SPI1_end_communication();

    // return value
    return chip_id;
}

void SPI1_start_communication(void)
{
    // begin SPI1 communication by setting CS low
    GPIOA->ODR &= ~SPI1_CS;
}

void SPI1_end_communication(void)
{
    // end SPI1 communication by setting CS high
    GPIOA->ODR |= SPI1_CS;
}