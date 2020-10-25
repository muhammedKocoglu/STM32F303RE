#include "stm32f3xx.h"                  // Device header

void USART_Init(void);
void AdelayMS(int delay);
char USART_Read(void);
void LED_play(int value);

int main (void){	
	USART_Init();	
	GPIOA->MODER |= 0x400; //for led
	char ch;
	while(1){
		ch=USART_Read();
		LED_play(ch);
	}
	
}


void USART_Init(void){	
  //Clock configurations for USART and TX	
	RCC->APB1ENR |=0x20000;
	RCC->AHBENR  |=0x20000;

	//AFR selection for PA3 and AFR mode selection for PA3
	GPIOA->AFR[0] |=0x7000;
	GPIOA->MODER |= 0x80;

	//USART Baund Rate
	USART2->BRR |= 0x0341; //9600
	// baud rate= fclk/usartdiv (for oversampling=8)
	// OVER8(bit15 of cr1)=0 -> oversampling =8
	// fclk=8 mhz
	
		
	//Enable Rx and USART
	USART2->CR1 |= 0x04;
	USART2->CR1 |= 0x01;
}

char USART_Read(void){
	while(!(USART2->ISR & 0x0020));
	return USART2->RDR;
}
	
void LED_play(int value){
	value %= 16;
	for(; value > 0;value--){
		GPIOA->BSRR =0x20;
		AdelayMS(100);
		GPIOA->BSRR = 0x200000;
		AdelayMS(100);
	}
	AdelayMS(400);
}
	
void AdelayMS(int delay){
	int i;
	for (;delay>0;delay--){
		for (i=0;i<3195;i++){
		GPIOA->ODR |= 0x00;   	
		}
	}
}
