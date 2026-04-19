#ifndef RUSH00_H
# define RUSH00_H
# pragma once

# include "embd.h"

# include <avr/io.h>
# include <util/delay.h>

# include "i2c.h"

#define DEBOUNCE_MS 30

typedef enum
{
    offline,
    idle,
    player_ready,
    opponent_ready,
    countdown,
    running,
    player_finished,
    opponent_finished,
} state_t;

enum {  EVNT_BTN,
        EVNT_TM1,
        EVNT_TM2,
        EVNT_RCV_RDY,
        EVNT_RCV_FNSH,
};

extern volatile state_t state;
extern volatile uint8_t event;
extern volatile uint8_t debounce_lock;
extern volatile uint8_t sec_counter;
extern volatile uint16_t ms_counter;
extern volatile uint16_t ms_opponent;
extern volatile uint16_t score;

void debounce_start(void);

void timer0_init(void);
void timer1_init(void);
void timer1_stop(void);
void timer2_init(void);
void timer2_stop(void);

void int0_init(void);

void reset_game(void);
void init_game(void);
uint8_t send_ready(void);
uint8_t send_score(const uint16_t score);
void start_countdown(void);
void print_score(void);
void check_win(void);
void animation_win(void);

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char* str);
void uart_print_uint16(uint16_t val);

void    handleEventButton(void);
void    handleEventTimer1(void);
void    handleEventTimer2(void);
void    handleEventReady(void);
void    handleEventFinish(void);

#endif
