#include "main.h"

volatile uint8_t pos = 0;

void timer1_start(void)
{
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 12499;                       // 50ms at 16MHz, prescaler 64
    TCCR1B |= (1 << WGM12);              // CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64
    TIMSK1 |= (1 << OCIE1A);             // enable compare interrupt
    SREG |= (1 << 7);                    // global interrupt enable
}

void timer1_stop(void)
{
    TCCR1B = 0;              // stop timer
    TIMSK1 &= ~(1 << OCIE1A); // disable interrupt
    pos = 0;
}

__attribute__((signal,used))
void TIMER1_COMPA_vect(void)
{
    wheel(pos++);
    update_rgb();
}