#include "main.h"

int main(void)
{
    uint8_t prev = 0;

    spi_init();
    adc_init();

    while (1)
    {
        uint8_t current = adc_read();
        if (current != prev)
        {
            if (current < 256 / 3 - 1) set_led_0();
            else if (current < 256 / 3 * 2 - 1) set_led_33(0xFF, 0, 0);
            else if (current < 256 - 1) set_led_66(0, 0, 0xFF);
            else set_led_100(0, 0xFF, 0);
            prev = current;
        }
        _delay_ms(10);
    }
}