#include <stdio.h>
#include "header.h"


int main(void)
{
    rcc_init();
    gpio_init();
    usart_init();
    timer_init();
    lcd_init();
    

    printf("LCD Example\r\n");
    lcd_print_string("hello world!");
    while (1)
    {
	    usart_tx(usart_rx());
    }
}

/*
 * ToDo:
 */
