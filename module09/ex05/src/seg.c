#include "main.h"

void seg_display(uint8_t value)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(EXP_PORT1);
    i2c_write(value);
    i2c_stop();
}

void seg_select(uint8_t digit)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(EXP_PORT0);
    i2c_write(digit);
    i2c_stop();
}

void seg_write(uint8_t value, uint8_t digit)
{
    seg_select(0xFF);
    seg_display(value);
    seg_select(digit);
}