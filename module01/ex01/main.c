#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB1); // set PB1 as output (LED)

    TCCR1A = (1 << COM1A0); // toggle OC1A on compare match
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode + prescaler 1024

    OCR1A = F_CPU / 1024UL / 2; // ~500 ms toggle (depends on F_CPU = 16MHz)

    while (1); // empty loop, all PWM generation handled by hardware
}