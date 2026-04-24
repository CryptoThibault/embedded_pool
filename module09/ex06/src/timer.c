#include "main.h"

const uint8_t seg_digits[10] =
{
    SEG_0, SEG_1, SEG_2, SEG_3, SEG_4,
    SEG_5, SEG_6, SEG_7, SEG_8, SEG_9
};

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);              // CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64 → 4µs/tick
    OCR0A = 249;                        // 1ms interrupt base
    TIMSK0 |= (1 << OCIE0A);            // interupt on
}

__attribute__((signal, used))
void TIMER0_COMPA_vect(void)
{
    static uint8_t ms = 0;

    ms++;

    if (ms % 4 == 0) seg_write(seg_digits[g_value % 10], DGT_4);
    else if (ms % 4 == 1) seg_write(seg_digits[g_value / 10 % 10], DGT_3);
    else if (ms % 4 == 2) seg_write(seg_digits[g_value / 100 % 10], DGT_2);
    else if (ms % 4 == 3) seg_write(seg_digits[g_value / 1000 % 10], DGT_1);
}