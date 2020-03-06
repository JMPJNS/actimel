#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    PORTA = 0b10000000;
    PORTB = 0b00000000;
    int8_t DIRECTION = 0;

    while (1) {
      _delay_ms(100);

      if (DIRECTION == 0 && PORTA == 0b10000000)
        DIRECTION = 1;

      if (DIRECTION == 1 && PORTA == 0b00000001) {
        PORTA = 0b00000000;
        PORTB = 0b10000000;
        continue;
      }

      if (DIRECTION == 1 && PORTB == 0b01000000)
        DIRECTION = 0;

      if (DIRECTION == 0 && PORTB == 0b10000000) {
        PORTA = 0b00000001;
        PORTB = 0b00000000;
        continue;
      }

      if (PORTA != 0b00000000)
        PORTA = (DIRECTION == 0 ? PORTA << 1 : PORTA >> 1);
      if (PORTB != 0b00000000)
        PORTB = (DIRECTION == 0 ? PORTB << 1 : PORTB >> 1);
    }
}