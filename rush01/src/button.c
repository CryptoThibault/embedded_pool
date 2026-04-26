#include "main.h"

volatile uint8_t last_state;

void pcint_init(void)
{
    DDRD &= ~((1 << PD2) | (1 << PD4) | (1 << PD7));
    PORTD |= (1 << PD2) | (1 << PD4) | (1 << PD7);
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT20) | (1 << PCINT23);
    last_state = PIND;
}

__attribute__((signal, used))
void PCINT2_vect(void)
{
    board.running = 1;

    uint8_t changed = PIND ^ last_state;
    last_state = PIND;

    if (changed & (1 << PD2)) events |= EVENT_BTN1;

    if (changed & (1 << PD4)) events |= EVENT_BTN2;

    if (changed & (1 << PD7)) events |= EVENT_BTN3;
}