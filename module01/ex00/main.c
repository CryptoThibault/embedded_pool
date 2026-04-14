#include <avr/io.h>

void delay_500ms()
{
    volatile unsigned long i;
    for (i = 0; i < 250000; i++)
        asm volatile("nop");
}

int main()
{
    DDRB |= (1 << PB1); // set PB1 as output (LED)

    while (1)
    {
        PORTB ^= (1 << PB1); // toggle PB1 (LED ON/OFF)
        delay_500ms();
    }
}