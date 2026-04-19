#include "rush00.h"

void int0_init(void)
{
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EICRA |= (1 << ISC00);
    EICRA &= ~((1 << ISC01));

    EIMSK |= (1 << INT0);
}

__attribute__((signal, used))
void INT0_vect(void)
{
    static uint8_t button_state = 0;

    if (debounce_lock) return;
    debounce_start();

    if (button_state == 0)
        event |= MASK(EVNT_BTN);
    button_state ^= 1;
}