#include "stm32f3xx.h"                  // Device header

int main()
{
	RCC->AHBENR |=0x20000;
	GPIOA->AFR[0] |=0x00100000;
	GPIOA->MODER |= 0x00000800;
	
	//Timer
	
	RCC->APB1ENR |=0x01;
	TIM2->PSC = 10-1;
	TIM2->ARR = 26667-1;
	TIM2->CNT =0;
	TIM2->CCMR1=0x0060;  	//ENABLE PWM MODE
	TIM2->CCER=1;					//ENABLE PWM CH1
	TIM2->CCR1=2000-1;		//PULSE WIDTH 1/3 THE PERIOD
	TIM2->CR1=1;					
	
	
	while(1){}
	
	/*
		Pulse Width Modulation mode allows you to generate a signal with a frequency determined
		by the value of the TIMx_ARR register and a duty cycle determined by the value of the
		TIMx_CCRx register
	*/
	
}
