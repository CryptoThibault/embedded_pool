#include "main.h"
void gauge(uint8_t pos)
{
    PORTB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB4);

    if (pos >= 63) PORTB |= (1 << PB0);
    if (pos >= 127) PORTB |= (1 << PB1);
    if (pos >= 191) PORTB |= (1 << PB2);
    if (pos == 255) PORTB |= (1 << PB4);
}

int main(void)
{
    uint8_t prev = 0;

    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

    init_rgb();
    adc_init();

    while (1)
    {
        uint8_t current = adc_read();
        if (current != prev)
        {
            wheel(current);
            gauge(current);
            prev = current;
        }
        _delay_ms(10);
    }
}