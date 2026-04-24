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

    if (ms % g_size == 0) seg_write(seg_digits[g_value % 10], DGT_4);
    else if (ms % g_size == 1 && g_value > 9) seg_write(seg_digits[g_value / 10 % 10], DGT_3);
    else if (ms % g_size == 2 && g_value > 99) seg_write(seg_digits[g_value / 100 % 10], DGT_2);
    else if (ms % g_size == 3 && g_value > 999) seg_write(seg_digits[g_value / 1000 % 10], DGT_1);
}

void timer1_init(void)
{
    TCCR1B |= (1 << WGM12); // Mode CTC
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler = 1024   
    OCR1A = 15624; // Compare value for 1s
    TIMSK1 |= (1 << OCIE1A); // Enable interrupt on compare match A
}

__attribute__((signal, used))
void TIMER1_COMPA_vect(void)
{
    g_value++;
    if (g_value > 9999)
    {
        g_value = 0;
        g_size = 1;
    }
    if (g_value >= 10)   g_size = 2;
    if (g_value >= 100)  g_size = 3;
    if (g_value >= 1000) g_size = 4;
}