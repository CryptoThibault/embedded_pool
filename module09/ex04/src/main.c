#include "main.h"

int main(void)
{
    i2c_init();
    exp_init();

    while (1)
    {
        seg_select(0xFF);
        seg_display(SEG_4);
        seg_select(DGT_3);
        _delay_ms(2);

        seg_select(0xFF);
        seg_display(SEG_2);
        seg_select(DGT_4);
        _delay_ms(2);
    }
}