#include "main.h"

int main(void)
{
    spi_init();

    spi_start();
    spi_set_led(0xFF, 0, 0, 0xFF);
    spi_set_led(0, 0, 0, 0xE0);
    spi_set_led(0, 0, 0, 0xE0);
    spi_stop();
    
    while (1);
}