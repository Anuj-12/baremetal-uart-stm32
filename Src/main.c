// To check which GPIO is mapped for Tx and Rx
// Check the alternate function table

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"

int main(){

	uart2_tx_init();

	while(1){
		printf("Hello from STM32F401....\n\r");
	}
}









