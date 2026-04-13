#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
    static unsigned int ms;

    if (++ms >= 500)
    {
        ms = 0; // reset counter after 500 interrupts (~500 ms)
        PINB = (1 << PB1); // toggle LED: write 1 to PINB toggles PB1 (AVR hardware behavior)
    }
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