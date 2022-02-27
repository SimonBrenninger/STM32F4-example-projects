#include "header.h"

void USART1_SendString(char *str)
{
    // loop through characters
    while(*str != '\0')
    {
        USART1_TX(*str);
        str++;
    }
}

void USART1_SendHex(uint8_t val)
{
    uint8_t idx;
    char ch = '0';

    // loop through first half of byte
    idx = 0x10;
    while(idx != 0x00)
    {
        if(val & idx)
        {
            ch += (idx >> 4);
        }
        idx <<= 1;
    }
    if(ch > '9')
        ch = 'A' + (ch-'9' - 1);
    // print first character
    USART1_TX(ch);

    ch = '0';
    // loop through second half of byte
    idx = 0x01;
    while(idx != 0x10)
    {
        if(val & idx)
        {
            ch += idx;
        }
        idx <<= 1;
    }
    if(ch > '9')
        ch = 'A' + (ch-'9' - 1);
    // print second character
    USART1_TX(ch);
}

char USART1_RX(void)
{
    char c;
    // wait until a character is recieved
    while(!(USART1->SR & USART_SR_RXNE));

    // read received character from data register DR
    c = USART1->DR;
    return c;
}

void USART1_TX(char c)
{
    // wait until DR is empty
    while(!(USART1->SR & USART_SR_TXE));

    // write byte into data register DR
    USART1->DR = c;

    // wait until transmission is completed
    while(!(USART1->SR & USART_SR_TC));

    if(USART1->SR & USART_SR_TC)
    {
        GPIOC->ODR ^= GPIO_ODR_OD13;
    }
}

void USARTConfig(void)
{
    // enable USART1 clock (48,8kHz)
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // enable USART1
    USART1->CR1 |= USART_CR1_UE;

    // 8 data bits (0b0)
    USART1->CR1 &= ~USART_CR1_M;
    // 0 parity bits (0b0)
    USART1->CR1 &= ~USART_CR1_PCE;
    // 1 stop bit (0b00)
    USART1->CR2 &= ~USART_CR2_STOP_Msk;

    /*          calculate baudrate
     * 
     * baud = f / (8 * (2-OVER8) * USARTDIV)
     * USARTDIV = f / (8 * (2-OVER8) * baud)
     * USARTDIV = 48,8kHz / (8 * (2-0) * 9600)
     * USARTDIV = 122,07
     * 
     * Mantissa = 0d122 = 0x7A
     * Fraction = 0d0.07 * 16 = 0d1 = 0x01
     */

    // set mantissa
    USART1->BRR &= ~USART_BRR_DIV_Mantissa_Msk;
    USART1->BRR |= (0x02 << USART_BRR_DIV_Mantissa_Pos);//2
    // set fraction
    USART1->BRR &= ~USART_BRR_DIV_Fraction_Msk;
    USART1->BRR |= (0x09 << USART_BRR_DIV_Fraction_Pos);//9
    // enable RX and TX
    USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);
}