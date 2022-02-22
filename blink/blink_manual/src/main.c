#include "stm32f411xe.h"

void GPIOConfig(void)
{
	// enable GPIO clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	// set pin PC13 as output (MODER: Output = 01)
	GPIOC->MODER |=  GPIO_MODER_MODER13_0;	//PC13 (bit25 high)
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;	//PC13 (bit26 low)

	// set pin PA0 as input (MODER: Input = 00)
	GPIOA->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1);	//(bit0 & bit1 low)

	// enable internal pullup on pin PA0
	GPIOA->PUPDR |=  GPIO_PUPDR_PUPD0_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_1;
}

void sleep(volatile uint32_t time)
{
	while(time--);
}

int main(void)
{
	int pa0_prev = GPIO_IDR_ID0;
	GPIOConfig();

	while(1)
	{
		// current state changed since prev value (any edge)
		if((GPIOA->IDR & GPIO_IDR_ID0) != pa0_prev)
		{
			// previous state of PA0 was 1 (falling edge)
			if(pa0_prev == (1 << GPIO_IDR_ID0_Pos))
			{
				// toggle pin PC13
				GPIOC->ODR ^= GPIO_ODR_OD13;
				// software debounce
				sleep(50000);
			}
			// update previous state of PA0
			pa0_prev = (GPIOA->IDR & GPIO_IDR_ID0);
		}
	}
}
