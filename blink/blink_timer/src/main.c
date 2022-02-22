#include "header.h"

int main(void)
{
	SysClockConfig();
	GPIOConfig();
	TIM2Config();

	while(1)
	{
		// do nothing
		// toggle PC13 in isr handler of TIM2
	}
	return 0;
}
