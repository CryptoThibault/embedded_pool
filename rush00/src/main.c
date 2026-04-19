#include "rush00.h"

volatile state_t state = idle;
volatile uint8_t debounce_lock = 0;
volatile uint8_t sec_counter = 0;
volatile uint16_t ms_counter = -1;
volatile uint16_t ms_opponent = -1;
volatile uint16_t score = 0;

int main(void)
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD3);
    timer0_init();
    int0_init();
    INTERUPT_ON;

    reset_game();
    sendOffline();
    while (1)
    {
        if (event) {
            if (event & MASK(EVNT_BTN)) {
                handleEventButton();
            }
            if (event & MASK(EVNT_TM1)) {
                handleEventTimer1();
            }
            if (event & MASK(EVNT_TM2)) {
                handleEventTimer2();
            }
            if (event & MASK(EVNT_RCV_RDY)) {
                handleEventReady();
            }
            if (event & MASK(EVNT_RCV_FNSH)) {
                handleEventFinish();
            }
        }
    }
}

