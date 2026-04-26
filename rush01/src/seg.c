#include "main.h"

const uint8_t seg_digits[10] =
{
    SEG_0, SEG_1, SEG_2, SEG_3, SEG_4,
    SEG_5, SEG_6, SEG_7, SEG_8, SEG_9
};

void seg_display(uint8_t value)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(EXP_PORT1_OUT);
    i2c_write(value);
    i2c_stop();
}

void seg_select(uint8_t digit)
{
    i2c_start();
    i2c_write(EXP_ADDR << 1);
    i2c_write(EXP_PORT0_OUT);
    board.exp_port0 = digit << 4 | board.exp_port0 & 0x0F;
    i2c_write(board.exp_port0);
    i2c_stop();
}

void seg_write(uint8_t value, uint8_t digit)
{
    seg_select(0xFF);
    seg_display(value);
    seg_select(digit);
}

void seg_print_value(void)
{
    uint8_t size = 1;
    if (board.value > 9) size++;
    if (board.value > 99) size++;
    if (board.value > 999) size++;

    if (ms % size == 0)
        seg_write(seg_digits[board.value % 10], DGT_4);
    else if (ms % size == 1 && board.value > 9)
        seg_write(board.mode >= 5 && board.mode <= 7
            ? seg_digits[board.value / 10 % 10] | (1 << 7)
            : seg_digits[board.value / 10 % 10], DGT_3);
    else if (ms % size == 2 && board.value > 99)
        seg_write(seg_digits[board.value / 100 % 10], DGT_2);
    else if (ms % size == 3 && board.value > 999)
        seg_write(seg_digits[board.value / 1000 % 10], DGT_1);
}

void seg_print_42(void)
{
    seg_write(SEG_D, DGT_4);
    seg_write(SEG_2, DGT_3);
    seg_write(SEG_4, DGT_2);
    seg_write(SEG_D, DGT_1);
}

void seg_print_time(void)
{
    if (ms % 4 == 0)
        seg_write(seg_digits[board.value % 10], DGT_4);
    else if (ms % 4 == 1)
        seg_write(seg_digits[board.value / 10 % 10], DGT_3);
    else if (ms % 4 == 2)
        seg_write(seg_digits[board.value / 100 % 10], DGT_2);
    else if (ms % 4 == 3)
        seg_write(seg_digits[board.value / 1000 % 10], DGT_1);
}