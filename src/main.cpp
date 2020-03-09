/*
 * Lauflicht.cpp
 *
 * Created: 3/6/2020 8:48:22 AM
 * Author : Jonas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;

	
    uint16_t counter = 0;
	
    while (1) 
    {
		if(PORTA == 0xFF) PORTA = 0x00;
		if(counter == 0xFFFF) {
			counter = 0;
			PORTA++;
		}
		counter++;
    }
}
