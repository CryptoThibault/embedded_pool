#include <avr/io.h>
#include <util/delay.h>

int main()
{
    uint8_t duty = 10;
    uint8_t prev1 = 1;  // previous state SW1 (pull-up = 1 idle)
    uint8_t prev2 = 1;  // previous state SW2

    DDRB |= (1 << PB1); // set PB1 as output (LED)

    DDRD &= ~((1<<PD2)|(1<<PD4)); // set buttons as input

    TCCR1A = (1 << COM1A1) | (1 << WGM11); // non-inverting PWM mode (clear on compare, set at BOTTOM)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // Fast PWM mode 14 + prescaler 1024

    ICR1 = F_CPU / 1024UL - 1; // set TOP for 1 Hz PWM period (1 second)
    
    while (1)
    {
        OCR1A = (uint32_t)ICR1 * duty / 100; // set duty cycle

        uint8_t current1 = (PIND & (1<<PD2)) ? 1 : 0; // read SW1
        uint8_t current2 = (PIND & (1<<PD4)) ? 1 : 0; // read SW2

        if (!current1 && prev1 && duty < 100) duty += 10; // SW1 press
        if (!current2 && prev2 && duty > 10) duty -= 10;  // SW2 press

        prev1 = current1; // store SW1 state
        prev2 = current2; // store SW2 state

        _delay_ms(10); // debounce delay
    }
}