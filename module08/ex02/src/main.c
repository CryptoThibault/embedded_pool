#include "main.h"

int main(void)
{
    spi_init();

    while (1)
    {
        set_led_D6(0xFF, 0xFF, 0);
        _delay_ms(250);
        set_led_D7(0, 0xFF, 0xFF);
        _delay_ms(250);
        set_led_D8(0xFF, 0, 0xFF);
        _delay_ms(250);
        set_led_0();
        _delay_ms(250);
    }
}