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

void disable_rgb()
{
    // 1. disconnect PWM outputs FIRST
    TCCR0A &= ~((1 << COM0A1) | (1 << COM0B1));
    TCCR2A &= ~(1 << COM2B1);

    // 2. stop timers completely
    TCCR0B = 0;
    TCCR2B = 0;

    // 3. force pins LOW
    PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD3));
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r; // Red brightness (0 = off, 255 = max)
    OCR0A = g; // Green brightness (0 = off, 255 = max)
    OCR2B = b; // Blue brightness (0 = off, 255 = max)
}

void rgb_filter(uint8_t *rgb)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (rgb[i] < 5)
            rgb[i] = 0;
        else
            rgb[i] = (rgb[i] * rgb[i]) / 255;
    }
}