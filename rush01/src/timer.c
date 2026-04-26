#include "main.h"

volatile uint32_t ms = 0;
volatile uint8_t debounce_lock = 0;

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

void timer2_init(void)
{
    TCCR2A = (1 << WGM21); // CTC mode
    TCCR2B = (1 << CS22);  // prescaler 64 → 4µs/tick
    OCR2A = 249;           // 1ms interrupt base
    TIMSK2 = 0;            // interrupt OFF
}

void debounce_start(void)
{
    debounce_lock = 1;
    TCNT2 = 0;
    TIFR2 |= (1 << OCF2A);     // clear flag
    TIMSK2 |= (1 << OCIE2A);   // enable interrupt
}

__attribute__((signal, used))
void TIMER2_COMPA_vect(void)
{
    static uint8_t debounce_ms = 0;

    debounce_ms++;

    if (debounce_ms >= DEBOUNCE_MS)
    {
        debounce_ms = 0;
        debounce_lock = 0;
        TIMSK2 &= ~(1 << OCIE2A); // stop interrupt Timer2
    }
}