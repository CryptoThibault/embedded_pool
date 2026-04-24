#include "main.h"

void set_led_D6(uint8_t r, uint8_t g, uint8_t b)
{
    spi_start();
    spi_set_led(r, g, b, 0xFF);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
}

int main(void)
{
    spi_init();
    
    while (1)
    {
        set_led_D6(0xFF, 0, 0);
        _delay_ms(1000);
        set_led_D6(0, 0xFF, 0);
        _delay_ms(1000);
        set_led_D6(0, 0, 0xFF);
        _delay_ms(1000);
        set_led_D6(0xFF, 0xFF, 0);
        _delay_ms(1000);
        set_led_D6(0, 0xFF, 0xFF);
        _delay_ms(1000);
        set_led_D6(0xFF, 0, 0xFF);
        _delay_ms(1000);
        set_led_D6(0xFF, 0xFF, 0xFF);
        _delay_ms(1000);
    }
}