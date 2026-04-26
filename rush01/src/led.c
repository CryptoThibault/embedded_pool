#include "main.h"

void led_init(void)
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
}

void led_display_binary(uint8_t v)
{
    PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));

    PORTB |= (v & 1) << PB0;
    PORTB |= ((v >> 1) & 1) << PB1;
    PORTB |= ((v >> 2) & 1) << PB2;
    PORTB |= ((v >> 3) & 1) << PB4;
}