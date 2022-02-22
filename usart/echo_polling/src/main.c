#include "header.h"

int main(void)
{
	char recv;

	RCCConfig();
	GPIOConfig();
	USARTConfig();

	// print hello world message
	//USART1_SendString("Hi\r\n");

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
 * 
 * ToDo:
 * when using SendString first character does not get printed over UART
 * and Error: "Starting execution at address 0x08000000... Got byte 0x00 instead of ACK
 * failed." occurs.
 * implement own printf() function.
 */