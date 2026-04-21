#include "main.h"

void i2c_init(void)
{
    TWSR = 0x00;        // prescaler = 1
    TWBR = 72;          // 100 kHz pour 16 MHz
    TWCR = (1 << TWEN); // enable TWI
}

void i2c_start(void)
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // send START condition
    while (!(TWCR & (1 << TWINT)));                   // wait for START to complete
    I2C_LOG();
}

void i2c_stop(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // send STOP condition
}

void i2c_status(void)
{
    uart_tx('[');
    uart_print_hex8(TWSR); // status code
    uart_tx(']');
}