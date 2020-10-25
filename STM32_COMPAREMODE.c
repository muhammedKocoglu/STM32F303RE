#include "stm32f3xx.h"                  // Device header


int main (void)
{
	RCC->AHBENR |= 0x20000;
	GPIOA->MODER |= 0x800;			//Set pa5 to AF
	GPIOA->AFR[0] |= 0x00100000;//Set pin af1 for tim2 ch1
	
	RCC->APB1ENR |=1;
	TIM2->PSC=1600-1;
	TIM2->ARR=10000-1;
	TIM2->CCMR1=0x30;						//Set output to toggle on match
	TIM2->CCR1=0;								//Set match mode
	TIM2->CCER|=1;							//Enable ch1 compame mode	
	TIM2->CNT=0;								//Clear counter
	TIM2->CR1=1;								//Enable Tim2
	int i;
	while(1){
	i=TIM2->CNT;
	}

}
