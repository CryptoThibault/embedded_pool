#include "main.h"

void update_rgb(void)
{
    spi_start();
    spi_set_led(leds[0].r, leds[0].g, leds[0].b, (leds[0].r || leds[0].g || leds[0].b ? 0xFF : 0xE0));
    spi_set_led(leds[1].r, leds[1].g, leds[1].b, (leds[1].r || leds[1].g || leds[1].b ? 0xFF : 0xE0));
    spi_set_led(leds[2].r, leds[2].g, leds[2].b, (leds[2].r || leds[2].g || leds[2].b ? 0xFF : 0xE0));
    spi_stop();
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    leds[0].r = r; leds[0].g = g; leds[0].b = b;
    leds[1].r = r; leds[1].g = g; leds[1].b = b;
    leds[2].r = r; leds[2].g = g; leds[2].b = b;
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