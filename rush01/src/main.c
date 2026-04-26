#include "main.h"

volatile t_board board;
volatile uint8_t events;

int main(void)
{    
    uart_init();
    led_init();
    rgb_init();
    adc_init();
    i2c_init();
    exp_init();
    timer0_init();
    pcint_init();

    INTERUPT_ON;

    update_startup();

    while (1)
    {
        update_modes();
        update_events();
    }
}