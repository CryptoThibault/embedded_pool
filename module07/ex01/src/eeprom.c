#include "main.h"

void eeprom_hexdump(void)
{
    for (uint16_t i = 0; i < E2END + 1; ++i) // size of EEPROM
    {
        if (i % 16 == 0)
        {
            uart_printstr("0000");
            uart_print_hex16(i);
            uart_tx(' ');
        }

        uint8_t val = eeprom_read_byte((uint8_t*)i); // read EEPROM byte
        uart_print_hex8(val);
        if (i % 2 != 0) uart_tx(' ');

        if (i % 16 == 15) uart_printstr("\r\n");
    }
}