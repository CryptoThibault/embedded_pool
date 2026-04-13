#include <avr/io.h>
#include <util/delay.h>

int main()
{
    uint8_t prev = 1;
    uint8_t active = 0;

    DDRB |= (1 << PB0); // set PB0 as output (LED)
    DDRD &= ~(1 << PD2); // set PD2 as input (button)

    PORTD |= (1 << PD2); // enable pull-up on PD2

    while (1)
    {
        uint8_t current = PIND & (1 << PD2) ? 1 : 0; // read PD2 state
        
        if (!current && prev)  // detect press
            active = !active; // toggle LED state
    
        prev = current; // update previous state

        if (active)
            PORTB |= (1 << PB0); // set PB0 high (LED on)
        else
            PORTB &= ~(1 << PB0); // set PB0 low (LED off)

        _delay_ms(10); // debounce delay
    }
}