#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB0); // set PB0 as output (LED)
    PORTB |= (1 << PB0); // set PB0 high (LED on)

    while (1);
}