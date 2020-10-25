#include "stm32f3xx.h"                  // Device header

int analogValue;

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	GPIOA->MODER |=0xC;
	GPIOA->MODER |=0x400;
	GPIOA->ODR |= 0x20;
	
	ADC1->CR 		=0;
	ADC1->SQR3	=1;
	ADC1->CR 		|=0x01;

	
	while(1){
		ADC1->CR |=ADC_CR_ADSTART;
		while(!(ADC1->ISR & 0x04));
		analogValue=ADC1->DR;
	}
	
}