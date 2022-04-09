#include "header.h"

int main(void)
{
	RCCConfig();
	GPIOConfig();
	I2C1Config();
	USARTConfig();

	I2C1_start();
	I2C1_stop();

	while(1)
	{
		// start I2C communication
	}
}