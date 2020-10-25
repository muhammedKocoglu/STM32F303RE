#include "stm32f3xx.h"                  // Device header

//Led: PA5
//Button: PC13

void systicDelayMs(int n);

int main(void){
	
	__disable_irq();
	
	RCC->AHBENR |= 0xA0000; 		//Enable clock for PORTA and PORTC

	RCC->APB2ENR |=0x01;			//Enable clock for SYSCFG
	
	GPIOA->MODER |= 0x400;
	SYSCFG->EXTICR[3] = 0x0020;	//Select port C for EXTI13 
															//EXTI13 attached with EXTI4 register which is accesable with ESTICR[3]
	EXTI->IMR |= 0x2000;				//unmask EXTI13
	EXTI->FTSR|= 0x2000;				//Select falling edge trigger
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq();
	while(1){}
}

void EXTI15_10_IRQHandler (void){
	GPIOA->BSRR = 0x20;
	systicDelayMs(100);
	GPIOA->BSRR = 0x200000;
	systicDelayMs(100);
	GPIOA->BSRR = 0x20;
	systicDelayMs(100);
	GPIOA->BSRR = 0x200000;
	
	
	EXTI->PR = 0x2000;					//Clearing interrupt flag
	}

	
	void systicDelayMs(int n)
	{
		SysTick->LOAD =16000;
		SysTick->VAL =0;
		SysTick->CTRL=0x5;
		for (int i=0;i<n;i++){
			while((SysTick->CTRL & 0x10000)==0){}
			}
		SysTick->CTRL =0;
	}
