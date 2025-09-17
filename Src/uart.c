/*
 * uart.c
 *
 *  Created on: Sep 14, 2025
 *      Author: anuj
 */
#include "uart.h"

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define SYS_FREQ 		16000000	// Default clock 16MHz with RC Oscillator
#define APB1_PRESCALER 	4			// Prescaler is the factor by which clock is divided
#define APB1_CLK 		(SYS_FREQ / APB1_PRESCALER)

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define OVER8			0
#define UART_BAUD		115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint32_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void){
	/************ Configure UART GPIO pin ***********/
	// Enable clock access
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 to alternate function mode
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);

	// Set PA2 alternative function type to UART2 TX (AF07)
	// AFR[0] = AFRL, AFRH = AFR[1]
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8);

	/************ Configure UART module ************/
	// Enable clock access to uart2
	RCC->APB1ENR |= UART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUD);

	// Configure transfer direction
	// Control Register 1
	USART2->CR1 = CR1_TE;	// Not using OR, everything else becomes 0 in the register

	// Enable uart modules
	USART2->CR1 |= CR1_UE;

	// set prescaler for APB1 to 4
	RCC->CFGR &= ~(7 << 10);   // clear PPRE1
	RCC->CFGR |=  (5 << 10);   // set 0b101 → divide by 4

}

void uart2_write(int ch){
	// Make sure transmit data register is empty before writing
	// Check through the USART Status Register
	while (!(USART2->SR & SR_TXE)){

	}
	// Write to transmit data register
	USART2->DR = (ch & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
//	USARTx->BRR = 0x23;
}

static uint32_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	uint32_t usartdiv = (PeriphClk + (BaudRate/2U)) / BaudRate;

	return usartdiv;
}


