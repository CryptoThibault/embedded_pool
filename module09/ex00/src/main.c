#include "main.h"

int main(void)
{
    i2c_init();
    exp_init();

    while (1)
    {
        exp_invert_D6();
        _delay_ms(500);
    }
}
