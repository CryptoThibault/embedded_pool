#include "main.h"

volatile uint8_t debounce_lock = 0;

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);              // CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64 → 4µs/tick
    OCR0A = 249;                        // 1ms interrupt base
    TIMSK0 &= ~(1 << OCIE0A);           // interrupt OFF par défaut
}

void debounce_start(void)
{
    debounce_lock = 1;
    TCNT0 = 0;
    TIFR0 |= (1 << OCF0A);     // clear flag
    TIMSK0 |= (1 << OCIE0A);   // enable interrupt
}

__attribute__((signal, used))
void TIMER0_COMPA_vect(void)
{
    static uint8_t ms = 0;

    ms++;

    if (ms >= 30)   // 30ms debounce
    {
        ms = 0;
        debounce_lock = 0;
        TIMSK0 &= ~(1 << OCIE0A); // stop interrupt Timer0
    }
}