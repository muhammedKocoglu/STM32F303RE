#include "stm32f3xx.h"                  // Device header


int main(void)
{
	__disable_irq();
	
	RCC->AHBENR |=0x20000;
	GPIOA->MODER|=0x400;
	
	RCC->APB1ENR|=1;
	TIM2->PSC =8000-1;
	TIM2->ARR =1000-1;
	TIM2->CR1 =1;
	TIM2->DIER|=1;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	__enable_irq();
	
	while(1);
}

void TIM2_IRQHandler(void)
{
	TIM2->SR=0;
	GPIOA->ODR ^=0x20;
}
