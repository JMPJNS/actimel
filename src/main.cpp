/*
 * Lauflicht.cpp
 *
 * Created: 3/6/2020 8:48:22 AM
 * Author : Jonas
 */ 

#define F_CPU 1600000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	
    int direction = 1;
    PORTC = 0x01;
    PORTA = 0x00;
	
    while (1) 
    {
		_delay_ms(1000);
		
		if(direction && PORTA == 0 && PORTC == 0x02) {
			direction = 0;
		}
		
		if(!direction && PORTA == 0x01 && PORTC == 0) {
			direction = 1;
		}
		
		if(direction && PORTA == 0x80 && PORTC == 0) {
			PORTA = 0;
			PORTC = 0x01;
			continue;
		}
		
		if(!direction && PORTA == 0 && PORTC == 0x01) {
			PORTA = 0x80;
			PORTC = 0;
			continue;
		}
		
		if(PORTC != 0) {
			if (direction) {
				PORTC = PORTC << 1;
				} else {
				PORTC = PORTC >> 1;
			}
		}
		
		if(PORTA != 0) {
			if (direction) {
				PORTA = PORTA << 1;
				} else {
				PORTA = PORTA >> 1;
			}
		}
    }
}
