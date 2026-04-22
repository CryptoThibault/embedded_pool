#include "main.h"

int main()
{
    uart_init();

    while (1)
    {
        char buf[BUFFER_SIZE];
        uint8_t i = 0;
    
        uart_printstr("> ");
        while (!uart_line_process(buf, &i));

        uint8_t error = 0;
        uint16_t addr = 0;
        uint8_t data = 0;

        while (buf[i] != ' ' && buf[i] != '\0')
        {
            if (!is_hex(buf[i]))
            {
                error = 1;
                break;
            }
            
            addr = (addr << 4) | hex_to_val(buf[i++]);    
        }
        
        if (error)
        {
            uart_printstr("Error: bad address\r\n");
            continue;
        }
        else if (addr > E2END)
        {
            uart_printstr("Error: out of EEPROM range\r\n");
            continue;
        }

        if (buf[i] != ' ')
        {
            uart_printstr("Error: missing space\r\n");
            continue;
        }
        i++;

        if (!is_hex(buf[i]))
        {
            uart_printstr("Error: bad data\r\n");
            continue;
        }

        data = hex_to_val(buf[i++]);

        if (is_hex(buf[i])) data = (data << 4) | hex_to_val(buf[i++]);

        if (is_hex(buf[i]) || buf[i] != '\0')
        {
            uart_printstr("Error: bad data\r\n");
            continue;
        }

        if (data != eeprom_read_byte((uint8_t*)addr))
            eeprom_write_byte((uint8_t*)addr, data);
        else
            addr = -1;
        eeprom_hexdump(addr);
    }
}