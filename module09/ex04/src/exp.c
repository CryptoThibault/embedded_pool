#include "main.h"

void exp_init(void)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(0x02);
    i2c_write(0x00);
    i2c_stop();
}

uint8_t exp_read_gpio(void)
{
    uint8_t value;

    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(0x00);

    i2c_start();
    i2c_write((EXP_ADDR << 1) | 1);
    value = i2c_read_nack();
    i2c_stop();

    return value;
}