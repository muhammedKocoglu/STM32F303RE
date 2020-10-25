#include "stm32f3xx.h"                  // Device header

int main (void){
	
	RCC->AHBENR|= 0x20000;
	GPIOA-> MODER |= 0x400;
	
	//TIM2 CONFIG
	
	RCC-> APB1ENR |= 1;
	//   F  =  Fosc/(Prescaler*ReloadRegister)
	
	//F=1 için (1 sn sayma için):
	TIM2->PSC = 800-1; 		//8Mhz divided by 800
	TIM2->ARR = 10000-1;	//8Mhz/8 divided by 1000
	
	TIM2->CNT = 0;
	TIM2->CR1 = 1;
	
	while(1){
		while(!(TIM2->SR & 1)){}
		TIM2->SR &=~1;
		GPIOA->ODR ^=0x20;
	}
}
