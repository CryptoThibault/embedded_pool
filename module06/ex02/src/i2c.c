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
    while (TWCR & (1 << TWSTO));                      // wait for STOP to finish
}

void i2c_status(void)
{
    uart_tx('[');
    uart_print_hex8(TWSR); // status code
    uart_tx(']');
}

void i2c_write(unsigned char data)
{
    TWDR = data;                               // load data into data register
    TWCR = (1 << TWEN) | (1 << TWINT);         // start transmission
    while (!(TWCR & (1 << TWINT)));            // wait until done
    I2C_LOG();
}

void i2c_read(void)
{
    static uint8_t index = 0;

    if (index < 6) TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // ACK
    else TWCR = (1 << TWEN) | (1 << TWINT);            // NACK

    while (!(TWCR & (1 << TWINT))); // wait for data
    buf[index++] = TWDR;            // store data in global buffer
    if (index == 7) index = 0;
    I2C_LOG();
}

void ath20_read(void)
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
}
