#include "stm32f3xx.h"                  // Device header
#include <stdio.h>

void USART_Init(void);
int USART_write(int ch);
void AdelayMS(int delay);
char USART_Read(void);




int main(void){
	USART_Init();
	int n;
	char str[100];
	printf("Hello it's me\n\r");
	fprintf(stdout,"test for stdout\r\n");
	fprintf(stderr,"test for stderr\r\n");
	
	while(1){
		printf("how old are you?");
		scanf("%d",&n);
		printf("your age is: %d\r\n",n);
		printf("enter your first name: ");
		gets(str);
		printf("you are ");
		puts(str);
		printf("\r\n");
		
		fprintf(stdout,"test for stdout\r\n");
		fprintf(stderr,"test for stderr\r\n");
	}

}


void USART_Init(void){	
	
	
  //Clock configurations for USART and TX	
	RCC->APB1ENR |=0x20000;
	RCC->AHBENR  |=0x20000;

	//AFR selection for PA2 and AFR mode selection for PA2
	GPIOA->AFR[0] |=0x7700;
	GPIOA->MODER |= 0xA0;

	//USART Baund Rate
	USART2->BRR |= 0x0341; //9600
	// baud rate= fclk/usartdiv (for oversampling=8)
	// OVER8(bit15 of cr1)=0 -> oversampling =8
	// fclk=8 mhz
	
		
	//Enable Tx and USART
	USART2->CR1 |= 0x0C;
	USART2->CR1 |= 0x01;
}
int USART_write(int ch){
	while(!(USART2->ISR & 0x0080)){}
	USART2->TDR =(ch & 0xFF);
	return ch;
}

void AdelayMS(int delay){
	int i;
	for (;delay>0;delay--){
		for (i=0;i<3195;i++){
		GPIOA->ODR |= 0x20;   	
		}
	}
}
char USART_Read(void){
	

	while(!(USART2->ISR & 0x0020));
	return USART2->RDR;
}



FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f){
	int c;
	c=USART_Read();
	if (c=='\r'){
		USART_write(c);
		c='\n';
	}
	USART_write(c);
	return c;
}

int fputc(int c, FILE *f){
	return 	USART_write(c);	
}
