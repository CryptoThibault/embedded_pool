#include "rush00.h"

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);                 // CTC mode

    TCCR0B = (1 << CS01) | (1 << CS00);    // prescaler 64 → 4µs/tick

    OCR0A = 249;                           // 1ms interrupt base

    TIMSK0 &= ~(1 << OCIE0A);             // interrupt OFF par défaut
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

void timer1_init(void)
{
    sec_counter = 0;
    TCCR1A = 0;                    // CTC mode
    TCCR1B = (1 << WGM12);        // CTC

    TCCR1B |= (1 << CS12);        // prescaler 256

    OCR1A = 62499;                // 1 seconde

    TIMSK1 |= (1 << OCIE1A);      // enable interrupt
}

void timer1_stop(void)
{
    TIMSK1 &= ~(1 << OCIE1A); // disable interrupt

    TCCR1B = 0;               // stop clock

    TCNT1 = 0;                // reset counter
    TIFR1 |= (1 << OCF1A);   // clear pending interrupt flag
    PORTB = 0;
}

__attribute__((signal, used))
void TIMER1_COMPA_vect(void)
{
    event |= MASK(EVNT_TM1);
}

void timer2_init(void)
{
    ms_counter = 0;
    TCCR2A = (1 << WGM21);      // CTC mode
    TCCR2B = (1 << CS22);       // prescaler 64
    OCR2A = 249;                // ~1ms à 16MHz
    TIMSK2 = (1 << OCIE2A);    // interrupt enable
}

void timer2_stop(void)
{
    TIMSK2 &= ~(1 << OCIE2A); // stop interrupts
    TCCR2B = 0;               // stop clock
    TCNT2 = 0;                // reset counter
}

__attribute__((signal, used))
void TIMER2_COMPA_vect(void)
{
    event |= MASK(EVNT_TM2);
}