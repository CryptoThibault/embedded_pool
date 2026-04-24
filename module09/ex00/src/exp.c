#include "main.h"

void exp_init(void)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(0x02);
    i2c_write(0x00);
    i2c_stop();
}

void exp_invert_D6(void)
{
    static uint8_t state = 0xFF;

    state ^= (1 << 3);
    
    i2c_start();
    i2c_write(EXP_ADDR << 1); // I2C address of the GPIO expander
    i2c_write(EXP_PORT0);       // Register controlling LEDs
    i2c_write(state);
    i2c_stop();
}