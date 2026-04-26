#include "main.h"

volatile uint32_t ms = 0;

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);              // CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64 → 4µs/tick
    OCR0A = 249;                        // 1ms interrupt base
    TIMSK0 |= (1 << OCIE0A);            // interupt on
}

__attribute__((signal, used))
void TIMER0_COMPA_vect(void)
{  
    ms++;
    events |= EVENT_TIMER;
}
