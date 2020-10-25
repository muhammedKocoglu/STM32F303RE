#include "stm32f3xx.h"                  // Device header


int timeStamp=0;

int main(void){

	RCC->AHBENR |= 0x20000;
	GPIOA->MODER |=0x800;						//SET pa5 as alternate function
	GPIOA->AFR[0]|=0x00100000;			//Set pin to AF1 for Tim2 Ch1
	
	RCC->APB1ENR |=1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CCMR1 =0x30;							//Set output to toggle on match
	
	TIM2->CCR1 =0;									//Set match value
	TIM2->CCER |=1;									//Enable ch1 compare mode
	TIM2->CNT =0;										//Clear counter
	TIM2->CR1=1;										//Enable TIM2
	
	//Configure PA6 as input of Tim3 Ch1
	RCC->AHBENR |=0x20000;					
	GPIOA->MODER |=0x2000;					//Set PA6 to alternate function
	GPIOA->AFR[0] |=0x02000000;			//SET pin to AF2 for Tim2 Ch1
	
	RCC->APB1ENR |=2;
	TIM3->PSC=1600-1;
	TIM3->CCMR1 = 0x41;							//SET Ch1 to capture at every edge
	TIM3->CCER =1;
	TIM3->CR1=1;
	
	while(1){
		while(!(TIM3->SR & 2)){}
		timeStamp=TIM3->CCR1;
	}	
	
}
