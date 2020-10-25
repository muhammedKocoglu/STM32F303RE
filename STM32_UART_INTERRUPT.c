#include "stm32f3xx.h"                  // Device header

void LED_play(int value);
void UART2_Init(void);
void systickDelayMs(int n);

int main(void)
{
	__disable_irq();
	RCC->AHBENR |=0x20000;
	GPIOA->MODER|=0x400;
	UART2_Init();
	USART2->CR1|=0x0020; 	//ENABLE RX INTERRUPT FOR USART2 
	NVIC_EnableIRQ(USART2_IRQn);
	__enable_irq();
	while(1){}	
}

void UART2_Init(void)
{
	RCC->AHBENR=0x20000;
	RCC->APB1ENR|=0x20000;

	GPIOA->AFR[0] |=0x7000;
	GPIOA->MODER |= 0x0080;
	
	USART2->BRR |=0x0341;		//BAUD RATE
	USART2->CR1=0x0004;			//ENABLE RECIVER
	USART2->CR1|=0x01;			//ENABLE USART2

}

void LED_play(int value){
	value %= 16;
	for(; value > 0;value--){
		GPIOA->BSRR =0x20;
		systickDelayMs(100);
		GPIOA->BSRR = 0x200000;
		systickDelayMs(100);
	}
	systickDelayMs(400);
}

void systickDelayMs(int n){
	SysTick->LOAD = 8000; 		//1ms
	SysTick->VAL |=0;					
	SysTick->CTRL|=5;					//0x00...0101; [2] CLCSOURCE 1=Processor clock; [1] TICKINT 0=No Interrupt ; [0] ENABLE 1=counter enable   
	
	for (int i=0;i<n;i++){
		while((SysTick->CTRL & 0x10000) ==0);
	}
	SysTick->CTRL=0;
}

void USART2_IRQHandler(void)
{
	char c;
	if (USART2->ISR & 0x0020)		//(RECIVER DATA REGISTER IS NOT EMPTY)
	{
		c=USART2->RDR;
		LED_play(c);
	}

}
