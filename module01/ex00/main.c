#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << PB1); // set PB1 as output (LED)

    while (1)
    {
        PORTB ^= (1 << PB1); // toggle PB1 (LED ON/OFF)
        _delay_ms(500);      // wait 500 ms
    }
}