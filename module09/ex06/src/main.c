#include "main.h"

volatile uint16_t g_value = 0;

int main(void)
{
    i2c_init();
    exp_init();
    adc_init();
    timer0_init();

    SREG |= (1 << 7);

    while (1)
    {
        uint16_t val = adc_read();
        if (val != g_value)
            g_value = val;
        _delay_ms(10);
    }
}