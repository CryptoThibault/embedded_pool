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