#include "stm32f3xx.h"                  // Device header

int main(void)
{
	__disable_irq();
	RCC->AHBENR		|=	0x20000;
	GPIOA->MODER	|=	0x400;
	
	SysTick->LOAD	|=	8000000-1;
	SysTick->VAL	|=	0;
	SysTick->CTRL	|=	7;
	
	__enable_irq();
	while(1);
}

void SysTick_Handler(void){
	GPIOA->ODR	^=0x20;
}