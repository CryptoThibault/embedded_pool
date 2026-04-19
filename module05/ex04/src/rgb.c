#include "main.h"

void init_rgb()
{
    // RED + GREEN (Timer0)
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1); // Fast PWM mode + enable OC0A (green) and OC0B (red)
    TCCR0B = (1 << CS01) | (1 << CS00); // Set prescaler to 64 for Timer0 speed

    // BLUE (Timer2)
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1); // Fast PWM mode + enable OC2B (blue output)
    TCCR2B = (1 << CS22); // Set prescaler to 64 for Timer2 speed
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r; // Red brightness (0 = off, 255 = max)
    OCR0A = g; // Green brightness (0 = off, 255 = max)
    OCR2B = b; // Blue brightness (0 = off, 255 = max)
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