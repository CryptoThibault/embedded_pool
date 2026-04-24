#include "main.h"

t_led leds[3];
volatile uint8_t events;
uint8_t color = 0;
uint8_t id = 0;

int main(void)
{
    spi_init();
    adc_init();
    timer0_init();
    int0_init();
    pcint2_init();

    update_rgb();

    SREG |= (1 << 7);

    while (1)
    {
        if (events & EVENT_BTN1)
        {
            events &= ~EVENT_BTN1;
            int0_event();
        }

        if (events & EVENT_BTN2)
        {
            events &= ~EVENT_BTN2;
            pcint2_event();
        }
    }
}