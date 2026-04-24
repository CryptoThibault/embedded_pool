#include "main.h"

volatile uint16_t g_value = 0;
volatile uint8_t g_size = 1;

int main(void)
{
    i2c_init();
    exp_init();
    timer0_init();
    timer1_init();

    SREG |= (1 << 7);

    while (1);
}