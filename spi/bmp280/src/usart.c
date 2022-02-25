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
    // enable USART1 clock (100MHz)
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
     * USARTDIV = 100MHz / 8 * (2-0) * 115200)
     * USARTDIV = 54,25
     * 
     * Mantissa = 0d54 = 0x36
     * Fraction = 0d0.25 * 16 = 0d4 = 0x4
     */

    // set mantissa
    USART1->BRR &= ~USART_BRR_DIV_Mantissa_Msk;
    USART1->BRR |= (0x36 << USART_BRR_DIV_Mantissa_Pos);
    // set fraction
    USART1->BRR &= ~USART_BRR_DIV_Fraction_Msk;
    USART1->BRR |= (0x04 << USART_BRR_DIV_Fraction_Pos);
    // enable RX and TX
    USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);
}