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

uint8_t SPI1_transceive(uint8_t tx_byte)
{
    // wait until previous transmition is finished (TX register empty)
    while(!(SPI1->SR & SPI_SR_TXE));

    // transmit byte via SPI
    SPI1->DR = tx_byte;

    // wait until BSY is reset (SPI busy communicating or TX buffer is not empty)
    while(SPI1->SR & SPI_SR_BSY);
    while(!(SPI1->SR & SPI_SR_RXNE));

    // receive byte from SPI1
    tx_byte = SPI1->DR;

    // return received byte
    return tx_byte;
}

uint8_t SPI1_read_byte(uint8_t addr)
{
    // first transmit address over SPI
    SPI1_transceive(addr);
    // and during reception send some dummy data
    return SPI1_transceive(0x00);
}

uint8_t *SPI1_read_bytes(uint8_t addr, uint8_t num_bytes)
{
    int num_allocd = 0;
    uint8_t *data = malloc(0);

    // first transmit starting address
    SPI1_transceive(addr);

    while(num_allocd < num_bytes)
    {
        data = realloc(data, ++num_allocd * sizeof(uint8_t));
        // during reception send dummy data
        data[num_allocd-1] = SPI1_transceive(0x00);
    }

    //return byte-pointer
    return data;
}

void SPI1_write_byte(uint8_t addr, uint8_t data)
{
    // transmit addr over SPI1 and write value of 'data'
    // to given address
    SPI1_transceive(addr);
    SPI1_transceive(data);
}

uint8_t SPI1_BMP280_get_id(void)
{
    // send command to transmit chip id (adress 0xD0)
    // MSB is used as R/W bit (W=0, R=1); for reading MSB can be left as is
    uint8_t chip_id;

    // begin SPI1 communication
    SPI1_start_communication();

    // get result from BMP280 sensor
    chip_id = SPI1_read_byte(0xD0);

    // end SPI1 communication
    SPI1_end_communication();

    // return value
    return chip_id;
}

void SPI1_BMP280_get_data(void)
{
    // start SPI communication
    SPI1_start_communication();

    SPI1_BMP280_get_temp();
    SPI1_BMP280_get_press();

    // end SPI communication
    SPI1_end_communication();

    // use calibration data to compute correct values

    USART1_SendString("current temperature is: \n\r");
}

uint32_t SPI1_BMP280_get_temp(void)
{
    return 0;
}

uint32_t SPI1_BMP280_get_press(void)
{
    return 0;
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