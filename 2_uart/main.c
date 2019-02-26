#include "uart.h"
#include <stdint.h>
#include "gpio.h"
#include <stdio.h>
ssize_t _write(int fd, const void *buf, size_t count){
		char * letter = (char *)(buf);
		for(int i=0; i<count; i++){
			uart_send(*letter);
			letter++;
		}
		return count;
		}

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	uart_init();
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	iprintf("Norway has %d counties. \n\r", 18);

	//GPIO->OUTSET=(1<<13); 				//Her lærte vi å få radene til å lyse

    int sleep = 0;
	while(1){

		if(!(GPIO->IN & (1<<26))){			// Check if button B is pressed
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);	//turn on LED matrix if it is.
            }
            uart_send('B');
		}

		if(!(GPIO->IN & (1<<17))){			// Check if button A is pressed;
			for(int i=13; i <=15; i++){
				GPIO->OUTCLR=(1<<i);		//turn off LED matrix if it is.
        	}
            uart_send('A');
		}

		if(uart_read() != '\0'){
		  if((GPIO->IN & (1<<13))){
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);}
			}
			else {
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);}
				}

			}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
