//PA5
//AHB1
//RCC->AHB1ENR
//GPIOx_MODER
//GPIOx_ODR

#include "stm32f3xx.h"                  // Device header

void delayMS(int delay);

int main(void)
{
	RCC->AHBENR |= 0x00020000;
	
	GPIOA->MODER |= 0x400;
	
	
	while(1)
	{
		
		
		GPIOA->ODR = 0x20;
		delayMS(100);
		GPIOA->ODR = 0x00;
		delayMS(100);
			
		
	}
}

void delayMS(int delay)
{
	int i;
	for(; delay>0;delay--){
		for (i=0 ; i<3195 ; i++); 
		}
}
