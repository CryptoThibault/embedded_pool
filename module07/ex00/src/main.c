#include "main.h"

int main()
{
    uart_init();

    eeprom_hexdump();

    while (1);
}