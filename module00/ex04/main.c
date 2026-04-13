#include <avr/io.h>
#include <util/delay.h>

void displayBinary(uint8_t v)
{
    PORTB &= ~((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4)); // clear LED pins (PB0,PB1,PB2,PB4)

    PORTB |= (v & 1) << PB0;        // bit0 -> PB0
    PORTB |= ((v >> 1) & 1) << PB1; // bit1 -> PB1
    PORTB |= ((v >> 2) & 1) << PB2; // bit2 -> PB2
    PORTB |= ((v >> 3) & 1) << PB4; // bit3 -> PB4
}

int main()
{
    uint8_t value = 0;  // displayed value (0-15)
    uint8_t pvalue = 0; // previous value
    uint8_t prev1 = 1;  // previous state SW1 (pull-up = 1 idle)
    uint8_t prev2 = 1;  // previous state SW2

    DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4); // set LEDs as output

    DDRD &= ~((1<<PD2)|(1<<PD4)); // set buttons as input

    PORTD |= (1<<PD2)|(1<<PD4); // enable pull-ups (idle = 1)

    while (1)
    {
        uint8_t current1 = (PIND & (1<<PD2)) ? 1 : 0; // read SW1
        uint8_t current2 = (PIND & (1<<PD4)) ? 1 : 0; // read SW2

        if (!current1 && prev1 && value < 15) value++; // SW1 press
        if (!current2 && prev2 && value > 0) value--;  // SW2 press

        prev1 = current1; // store SW1 state
        prev2 = current2; // store SW2 state

        if (value != pvalue) displayBinary(value); // update LEDs only if changed

        pvalue = value; // save last value

        _delay_ms(10); // debounce delay
    }
}