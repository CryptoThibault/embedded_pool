#include <avr/io.h>
#include <util/delay.h>

void init_rgb()
{
    DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    PORTD &= ~(1 << PD3) & ~(1 << PD5) & ~(1 << PD6);

    if (r) PORTD |= (1 << PD5);
    if (g) PORTD |= (1 << PD6);
    if (b) PORTD |= (1 << PD3);
}

void wheel(uint8_t pos)
{
    pos = 255 - pos;

    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

int main()
{
    uint8_t pos = 0;

    init_rgb();

    while (1)
    {
        wheel(pos++);
        _delay_ms(10);
    }
}
