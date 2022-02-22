#include "header.h"

int main(void)
{
	SysClockConfig();
	GPIOConfig();
	TIM2Config();

	while(1)
	{
		// do nothing
		// fade PA1 in isr handler of TIM2 Ch2
	}
}

/* 
 * Bugs resolved:
 * in gpio.c: configured wrong pin as alternate function (PA0 instead of PA1)
 * in tim2.c: TIM2_IRQHandler: changed direction with "dir -= dir" instead of "dir = -dir"
 * 
 * ToDo:
 * in header.h: change PWM_STEPS from absolute to relative (%) duty cycle steps
*/