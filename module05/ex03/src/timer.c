#include "main.h"

void timer1_init(void)
{
    TCCR1A = 0;                               // mode normal
    TCCR1B = (1 << WGM12);                    // CTC mode

    TCCR1B |= (1 << CS11) | (1 << CS10);      // prescaler 64

    OCR1A = 4999;                             // 20ms

    TIMSK1 |= (1 << OCIE1A);                  // enable interrupt
}

void TIMER1_COMPA_vect(void) __attribute__((signal));

void TIMER1_COMPA_vect(void)
{
    uint16_t val = adc_read_temp();
    int16_t temp = (val - 324) * 100 / 122;
    uart_print_uint16(temp);
    uart_printstr("\r\n");
}