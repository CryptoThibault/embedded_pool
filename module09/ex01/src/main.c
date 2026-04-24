#include "main.h"

int main(void)
{
    uint8_t value = 0;
    uint8_t prev_sw3 = 1;

    i2c_init();
    exp_init();

    exp_display_binary(value);

    while (1)
    {
        uint8_t gpio = exp_read_gpio();
        uint8_t sw3 = gpio & 0x01;

        if (sw3 == 0 && prev_sw3 == 1)
        {
            if (++value > 7) value = 0;
            exp_display_binary(value);

            _delay_ms(50);
        }

        prev_sw3 = sw3;

        _delay_ms(10);
    }
}