#include "main.h"

int main(void)
{
    uart_init();
    adc_init();
    timer1_init();

    SREG |= (1 << 7);

    while (1);
}