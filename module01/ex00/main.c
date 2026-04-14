#include <avr/io.h>

int main()
{
    volatile unsigned long count = 0;

    DDRB |= (1 << PB1); // set PB1 as output (LED)

    while (1)
    {
        if (++count >= F_CPU / 64)
        {
            count = 0;
            PORTB ^= (1 << PB1); // toggle PB1 (LED ON/OFF)
        }
    }
}