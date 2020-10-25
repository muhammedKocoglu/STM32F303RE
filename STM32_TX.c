#include "stm32f3xx.h"                  // Device header


//APB1 17 bit for USART2
// Usart TX = PA2
#define a 0xC000;

void USART_Init(void);
void USART_write(int ch);
void AdelayMS(int delay);

int main (void){
	
USART_Init();
GPIOA->MODER |= 0x400; //for led

	
	while(1){		
		USART_write('M');
		AdelayMS(10);
		USART_write('E');
		AdelayMS(10);
		USART_write('R');
		AdelayMS(10);
		USART_write('V');
		AdelayMS(10);
		USART_write('E');
		AdelayMS(10);
		USART_write(' ');
		AdelayMS(10);
		USART_write('N');
		AdelayMS(10);
		USART_write('U');
		AdelayMS(10);
		USART_write('R');
		AdelayMS(10);		
		
		USART_write('\n');
		AdelayMS(200);
		USART_write('\r');
	}
}

void USART_Init(void){	
  //Clock configurations for USART and TX	
	RCC->APB1ENR |=0x20000;
	RCC->AHBENR  |=0x20000;

	//AFR selection for PA2 and AFR mode selection for PA2
	GPIOA->AFR[0] |=0x700;
	GPIOA->MODER |= 0x20;

	//USART Baund Rate
	USART2->BRR |= 0x0341; //9600
	// baud rate= fclk/usartdiv (for oversampling=8)
	// OVER8(bit15 of cr1)=0 -> oversampling =8
	// fclk=8 mhz
	
		
	//Enable Tx and USART
	USART2->CR1 |= 0x08;
	USART2->CR1 |= 0x01;
}

void USART_write(int ch){
	while(!(USART2->ISR & 0x0080)){}
	USART2->TDR =(ch & 0xFF);
}
	

void AdelayMS(int delay){
	int i;
	for (;delay>0;delay--){
		for (i=0;i<3195;i++){
		GPIOA->ODR |= 0x20;   	
		}
	}
}
