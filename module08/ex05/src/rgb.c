#include "main.h"

void update_rgb(void)
{
    spi_start();
    spi_set_led(leds[0].r, leds[0].g, leds[0].b, (leds[0].r || leds[0].g || leds[0].b ? 0xFF : 0xE0));
    spi_set_led(leds[1].r, leds[1].g, leds[1].b, (leds[1].r || leds[1].g || leds[1].b ? 0xFF : 0xE0));
    spi_set_led(leds[2].r, leds[2].g, leds[2].b, (leds[2].r || leds[2].g || leds[2].b ? 0xFF : 0xE0));
    spi_stop();
}