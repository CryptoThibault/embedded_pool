#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t duty = 50;

ISR(TIMER1_COMPA_vect)
{
    static unsigned int ms = 0; // time counter (ms)

    if (++ms < duty * 10) PORTB |= (1 << PB1); // LED ON during duty time
    else PORTB &= ~(1 << PB1); // LED OFF otherwise

    if (ms >= 1000) ms = 0; // reset 1s cycle
}

int main()
{
    uint8_t prev1 = 1;  // previous state SW1 (pull-up = 1 idle)
    uint8_t prev2 = 1;  // previous state SW2

    DDRB |= (1 << PB1); // set PB1 as output (LED)

    DDRD &= ~((1<<PD2)|(1<<PD4)); // set buttons as input

    TCCR1A = 0; // normal mode (no PWM)
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTC mode + prescaler 64
    OCR1A = 249; // 1 ms compare match value
    TIMSK1 = (1 << OCIE1A); // enable Timer1 compare interrupt

    sei(); // enable global interrupts

    while (1)
    {
        uint8_t current1 = (PIND & (1<<PD2)) ? 1 : 0; // read SW1
        uint8_t current2 = (PIND & (1<<PD4)) ? 1 : 0; // read SW2

        if (!current1 && prev1 && duty < 100) duty += 10; // SW1 press
        if (!current2 && prev2 && duty > 10) duty -= 10;  // SW2 press

        prev1 = current1; // store SW1 state
        prev2 = current2; // store SW2 state

        _delay_ms(10); // debounce delay
    }
}