#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << PB0); // set PB0 as output (LED)
    DDRD &= ~(1 << PD2); // set PD2 as input (button)

    PORTD |= (1 << PD2); // enable pull-up on PD2

    while (1)
    {
        if (!(PIND & (1 << PD2))) // read PD2 state
            PORTB |= (1 << PB0); // set PB0 high (LED on)
        else
            PORTB &= ~(1 << PB0); // set PB0 low (LED off)

        _delay_ms(10); // debounce delay
    }
}