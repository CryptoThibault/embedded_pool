#include "rush00.h"

volatile uint8_t event = 0b00000;

void    handleEventButton(void) {
    UNSET_BIT(event, EVNT_BTN);

    if (state == idle || state == offline)
    {
        init_game();
        state = player_ready;
        if (!send_ready()) return;
        PORTD |= (1 << PD3) | (1 << PD6);
    }
    else if (state == opponent_ready)
    {
        init_game();
        if (send_ready())
            start_countdown();
    }
    else if (state == countdown)
    {
        timer1_stop();
        sec_counter = 0;
        ms_counter = -1;
        if (!send_score(-1)) return;
        PORTD = (1 << PD5);
        state = player_finished;
    }
    else if (state == running)
    {
        state = player_finished;
        timer2_stop();
        if (!send_score(ms_counter)) return;
    }
    else if (state == opponent_finished)
    {
        timer1_stop();
        timer2_stop();
        if (!send_score(ms_counter)) return;
        check_win();
        state = idle;
    }
}

void    handleEventTimer1(void) {
    UNSET_BIT(event, EVNT_TM1);
    sec_counter++;

    if (sec_counter == 1) PORTB &= ~(1 << PB4);
    if (sec_counter == 2) PORTB &= ~(1 << PB2);
    if (sec_counter == 3) PORTB &= ~(1 << PB1);

    if (sec_counter == 4)
    {
        timer1_stop();
        PORTB &= ~(1 << PB0);
        if (state == countdown) state = running;
        sec_counter = 0;
        timer2_init();
    }
}

void    handleEventTimer2(void) {
    UNSET_BIT(event, EVNT_TM2);

    ms_counter++;

    if (ms_counter == 0)
    {
        timer2_stop();
        ms_counter = -1;
        if (!send_score(-1)) return;
        state = idle;
        check_win();
    }
}

void    handleEventReady(void) {
    UNSET_BIT(event, EVNT_RCV_RDY);
    if (state == idle) {
        PORTD = (1 << PD3) | (1 << PD5);
        state = opponent_ready;
    } else if (state == player_ready) {
        start_countdown();
    } else
        sendOffline();
}

void    handleEventFinish(void) {
    UNSET_BIT(event, EVNT_RCV_FNSH);
    if (state == running || state == countdown) {
        state = opponent_finished;
        ms_opponent = *(uint16_t *)(dataRecv.raw);
    } else if (state == player_finished) {
        ms_opponent = *(uint16_t *)(dataRecv.raw);
        check_win();
        state = idle;
    } else
        sendOffline();
}