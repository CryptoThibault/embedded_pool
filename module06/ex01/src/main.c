#include "main.h"

volatile uint8_t buf[7];

int main()
{
    uart_init();
    i2c_init();

    while (1)
    {
        i2c_start();
        i2c_write(AHT20_ADDR << 1 | TW_WRITE); // write mode
        i2c_write(AHT20_CMD_TRIGGER);
        i2c_write(AHT20_CMD_ARG1);
        i2c_write(AHT20_CMD_ARG2);
        i2c_stop();

        _delay_ms(80); // conversion time

        i2c_start();
        i2c_write(AHT20_ADDR << 1 | TW_READ); // read mode
        for (uint8_t i = 0; i < 7; i++)
            i2c_read();
        i2c_stop();

        for (uint8_t i = 0; i < 7; i++)
        {
            print_hex_value(buf[i]);
            uart_tx(' ');
        }
        uart_printstr("\r\n");

        _delay_ms(500);
    }
}