#include "main.h"

void event_btn1(void)
{
    static uint8_t state = 0;
    static uint32_t last = DEBOUNCE_MS;

    if (ms - last < DEBOUNCE_MS) return;

    if (state == 0)
    {
        state = 1;
        
        board.exp_port0 &= ~(1 << EXP_LED_D9_BIT);

        if (board.mode == 4) rgb_stop();

        if (board.mode < 10) board.mode++;
        else board.mode = 0;
        led_display_binary(board.mode);

        if (board.mode == 4) rgb_init();
    }
    else
    {
        state = 0;
        board.exp_port0 |= 1 << EXP_LED_D9_BIT;
    }

    last = ms;
}

void event_btn2(void)
{
    static uint8_t state = 0;
    static uint32_t last = DEBOUNCE_MS;

    if (ms - last < DEBOUNCE_MS) return;

    if (state == 0)
    {
        state = 1;

        board.exp_port0 &= ~(1 << EXP_LED_D10_BIT);

        if (board.mode == 4) rgb_stop();
        
        if (board.mode > 0) board.mode--;
        else board.mode = 10;
        led_display_binary(board.mode);

        if (board.mode == 4) rgb_init();
    }
    else
    {
        state = 0;
        board.exp_port0 |= 1 << EXP_LED_D10_BIT;
    }

    last = ms;
}

void event_btn3(void)
{
    static uint8_t state = 0;
    static uint32_t last = DEBOUNCE_MS;

    if (ms - last < DEBOUNCE_MS) return;

    if (state == 0)
    {
        state = 1;

        board.exp_port0 &= ~(1 << EXP_LED_D11_BIT);
    }
    else
    {
        state = 0;
        board.exp_port0 |= 1 << EXP_LED_D11_BIT;
    }

    last = ms;
}