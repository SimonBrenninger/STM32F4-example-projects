#include <stdio.h>
#include "header.h"

int main(void)
{
	char recv;

	RCCConfig();
	GPIOConfig();
	USARTConfig();

	// print hello world message
	USART1_SendString("\n\rHello World!\n\r");

	while(1)
	{
		// echo the received byte(s)

		// receive one byte
		// (blocking function; waits until 1 byte is received)
		recv = USART1_RX();

		// and send it back to transmitter
		USART1_TX(recv);
	}
}

/*
 * Bugs resolved:
 * in rcc.c: RCCConfig: flash latency not set (cpu clock 2fast for flash)
 * in usart.c: USARTConfig: usart receive and transmit functions for wrong peripheral (USART2)
 * in usart.c: USART1_SendString: first character got overwritten by second character
 * 			   (didn't check if transmit data register was empty (USART_SR_TXE))
 * 
 * ToDo:
 * and Error: "Starting execution at address 0x08000000... Got byte 0x00 instead of ACK
 * failed." occurs.
 * implement own printf() function.
 */