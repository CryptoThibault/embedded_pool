#include "rush00.h"

void init_game(void)
{
    PORTD = 0;
    PORTB = 0;
    ms_counter = -1;
    ms_opponent = -1;
}

uint8_t send_ready(void)
{
    return (sendState(player_ready));
}

void start_countdown(void)
{
    PORTD &= ~(1 << PD3) & ~(1 << PD5) & ~(1 << PD6);
    PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    state = countdown;
    timer1_init();
}

uint8_t send_score(const uint16_t score)
{
    return send((uint8_t*)&score, sizeof(score), player_finished);
}

void print_score(void)
{
    uart_printstr("Player score: ");
    uart_print_uint16(ms_counter);
    uart_printstr("ms | Opponent score: ");
    uart_print_uint16(ms_opponent);
    uart_printstr("ms\r\n");
}

void check_win(void)
{
    print_score();
    PORTD = 0;
    if (ms_counter < ms_opponent)
    {
        PORTD |= (1 << PD6);
        ++score;
    }
    else if (ms_counter > ms_opponent)
    {
        PORTD |= (1 << PD5);
    }
    else
    {
        PORTD |= (1 << PD5) | (1 << PD6);
    }
    SET_BIT_VAL(PORTB, PB0, score & 1);
    SET_BIT_VAL(PORTB, PB1, score & 2);
    SET_BIT_VAL(PORTB, PB2, score & 4);
    SET_BIT_VAL(PORTB, PB4, score & 8);
}

void animation_win(void)
{
    static uint8_t tick = 0;

    if (tick % 4 == 0) PORTB ^= (1 << PB0);
    if (tick % 8 == 0) PORTB ^= (1 << PB1);
    if (tick % 16 == 0) PORTB ^= (1 << PB2);
    if (tick % 32 == 0) PORTB ^= (1 << PB4);
    tick++;
    if (tick > 64) tick = 0;
    _delay_ms(10);
}

void reset_game(void)
{
    score = 0;
    state = offline;
    event = 0;
    PORTD = MASK(PD3);
    PORTB = 0;
}