#include "main.h"

void rgb_init(void)
{
    spi_init();
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD3);
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

void rgb_stop(void)
{
    PORTD &= ~(1 << PD5) & ~(1 << PD6) & ~(1 << PD3);
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
    spi_disable();
}

void rgb_display(void)
{
    static uint32_t last = 1000;
    static uint8_t color = 0;

    if (ms - last >= 1000)
    {
        switch (color)
        {
            case 0:
                PORTD &= ~(1 << PD3);
                PORTD |= (1 << PD5);
                spi_start();
                spi_set_led(0xFF, 0, 0, 0xF0);
                spi_set_led(0xFF, 0, 0, 0xF0);
                spi_set_led(0xFF, 0, 0, 0xF0);
                spi_stop();
                break;
            case 1:
                PORTD &= ~(1 << PD5);
                PORTD |= (1 << PD6);
                spi_start();
                spi_set_led(0, 0xFF, 0, 0xF0);
                spi_set_led(0, 0xFF, 0, 0xF0);
                spi_set_led(0, 0xFF, 0, 0xF0);
                spi_stop();
                break;
            case 2:
                PORTD &= ~(1 << PD6);
                PORTD |= (1 << PD3);
                spi_start();
                spi_set_led(0, 0, 0xFF, 0xF0);
                spi_set_led(0, 0, 0xFF, 0xF0);
                spi_set_led(0, 0, 0xFF, 0xF0);
                spi_stop();
                break;
        }
        if (++color >= 3) color = 0;
        last = ms;
    }
}