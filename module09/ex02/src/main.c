#include "main.h"

int main(void)
{
    i2c_init();
    exp_init();

    seg_display(SEG_2);
    seg_select(DGT_4);

    while (1);
}