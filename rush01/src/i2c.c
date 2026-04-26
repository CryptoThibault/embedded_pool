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
}

void i2c_stop(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // send STOP condition
    while (TWCR & (1 << TWSTO));                      // wait for STOP to finish
}

void i2c_write(uint8_t data)
{
    TWDR = data;                               // load data into data register
    TWCR = (1 << TWEN) | (1 << TWINT);         // start transmission
    while (!(TWCR & (1 << TWINT)));            // wait until done
}

uint8_t i2c_read_ack(void)
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // enable ACK
    while (!(TWCR & (1 << TWINT)));                  // wait
    return TWDR;
}

uint8_t i2c_read_nack(void)
{
    TWCR = (1 << TWEN) | (1 << TWINT); // no ACK
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}