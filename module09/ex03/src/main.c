#include "main.h"

const uint8_t seg_digits[10] =
{
    SEG_0, SEG_1, SEG_2, SEG_3, SEG_4,
    SEG_5, SEG_6, SEG_7, SEG_8, SEG_9
};

int main(void)
{
    uint8_t i = 0;

    i2c_init();
    exp_init();

    seg_select(DGT_4);

    while (1)
    {
        seg_display(seg_digits[i]);
        i < 9 ? ++i : (i = 0);
        _delay_ms(1000);
    }
}