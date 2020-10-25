#include "stm32f3xx.h"                  // Device header
void systickDelayMs(int n);


int main(void)
{
	
	RCC->AHBENR |= 0xA0000;
	GPIOA->MODER |= 0x400;
	

	SysTick->LOAD = 0x7A1200; // 1sn
	SysTick->VAL |=0;					//Current Value
	SysTick->CTRL|=5;					//0x00...0101; [2] CLCSOURCE 1=Processor clock; [1] TICKINT 0=No Interrupt ; [0] ENABLE 1=counter enable   
	
	while(1)
	{
		/*
		if (SysTick->CTRL & 0x10000){
		GPIOA->ODR ^=0x20;	}	
		*/
		systickDelayMs(1000);
		GPIOA->ODR ^=0x20;		
	}
}

//Function Format
//***************

void systickDelayMs(int n){
	SysTick->LOAD = 8000; 		//1ms
	SysTick->VAL |=0;					
	SysTick->CTRL|=5;					//0x00...0101; [2] CLCSOURCE 1=Processor clock; [1] TICKINT 0=No Interrupt ; [0] ENABLE 1=counter enable   
	
	for (int i=0;i<n;i++){
		while((SysTick->CTRL & 0x10000) ==0);
	}
	SysTick->CTRL=0;
}
