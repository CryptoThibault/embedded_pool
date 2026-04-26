#include "main.h"

void exp_init(void)
{
    i2c_start();
    // We start an i2c connection in write mode to the expander
    i2c_write(EXP_ADDR << 1);
    // We write to output registers
    i2c_write(EXP_PORT0_OUT);
    // We write 1 in to LEDS, because they have a pull-up
    board.exp_port0 = 0b1110;
    i2c_write(board.exp_port0);
    i2c_write(0);
    i2c_stop();

    i2c_start();
    // We start an i2c connection in write mode to the expander
    i2c_write(EXP_ADDR << 1);
    // We write to config registers
    i2c_write(EXP_PORT0_DIR);
    // We write 1 in bit 0 (button SW3) to put it in read mode
    i2c_write(0b1);
    i2c_write(0b0);
    i2c_stop();
}

uint16_t exp_read_gpio(void)
{
    uint8_t low, high;

    i2c_start();
    i2c_write(EXP_ADDR << 1  | TW_WRITE);
    i2c_write(0x00);

    i2c_start();
    i2c_write((EXP_ADDR << 1) | TW_READ);
    low = i2c_read_ack();

    high = i2c_read_nack();
    i2c_stop();

    return ((uint16_t)high << 8) | low;
}