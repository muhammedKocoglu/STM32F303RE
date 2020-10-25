#include "stm32f3xx.h"                  // Device header

int main(void)
{
  RCC->AHBENR |= 0x000A0000;
	//RCC->AHBENR |= 0x00020000;
	GPIOA->MODER |= 0x400;
	GPIOA->BSRR = 0x0020;
	
while(1)
{
	
	if(GPIOC->IDR & 0x2000)
	{
		GPIOA->BSRR = 0x200000;
	}
	else{
		GPIOA->BSRR = 0x20;
	}

} 
}
