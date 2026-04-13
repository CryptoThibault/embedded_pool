#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
    static unsigned int ms = 0;

    if (++ms < 100) PORTB |= (1 << PB1);   // LED ON for 100 ms
    else PORTB &= ~(1 << PB1);  // LED OFF for 900 ms

    if (ms >= 1000) ms = 0; // reset cycle every 1s
}

int main()
{
    DDRB |= (1 << PB1); // set PB1 as output (LED)

    TCCR1A = 0; // normal mode (no PWM)
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTC mode + prescaler 64
    OCR1A = 249; // 1 ms compare match value
    TIMSK1 = (1 << OCIE1A); // enable Timer1 compare interrupt

    sei(); // enable global interrupts

    while (1); // empty loop, everything handled by hardware + ISR
}