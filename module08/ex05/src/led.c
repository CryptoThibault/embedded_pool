#include "main.h"

void set_led_D6(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(r, g, b, 0xEA);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

void set_led_D7(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(r, g, b, 0xEA);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

void set_led_D8(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(r, g, b, 0xEA);
    spi_stop();
}

void blink_led(uint8_t id)
{
    if (id == 0) set_led_D6(0xFF, 0, 0);
    if (id == 1) set_led_D7(0xFF, 0, 0);
    if (id == 2) set_led_D8(0xFF, 0, 0);
    _delay_ms(50);
    update_rgb();
}