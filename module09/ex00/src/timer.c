#include "main.h"

void timer1_init(void)
{
    TCCR1A = 0;                   // CTC mode
    TCCR1B = (1 << WGM12);        // CTC mode
    TCCR1B |= (1 << CS12);        // prescaler 256
    OCR1A = 31249;                // 500 ms
    TIMSK1 |= (1 << OCIE1A);      // enable interrupt
}

__attribute__((signal, used))
void TIMER1_COMPA_vect(void)
{

}