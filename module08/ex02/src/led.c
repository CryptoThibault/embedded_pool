#include "main.h"

void set_led_D6(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(r, g, b, 0xFF);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

void set_led_D7(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(r, g, b, 0xFF);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

void set_led_D8(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(r, g, b, 0xFF);
    spi_stop();
}

void set_led_0(void)
{
    spi_start();
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}