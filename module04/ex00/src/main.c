#include <avr/io.h>
#include <avr/interrupt.h>

#define DEBOUNCE_MS 30

volatile uint8_t debounce_lock = 0;

void timer1_init()
{
    TCCR1A = 0;

    TCCR1B = (1 << CS11) | (1 << CS10); // prescaler 64 → 1 tick = 4 µs (16 MHz clock)
    TCCR1B &= ~(1 << WGM12); // normal mode

    TIMSK1 &= ~(1 << OCIE1A); // disable interrupt initially
}

void debounce_start()
{
    debounce_lock = 1;

    TCNT1 = 0;
    
    OCR1A = (DEBOUNCE_MS * 1000UL) / 4; // 30ms / 4µs = 7500 ticks

    TIFR1 |= (1 << OCF1A);     // clear flag
    TIMSK1 |= (1 << OCIE1A);   // enable compare interrupt
}

void int0_init()
{
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    // interrupt on ANY logical change (press + release)
    EICRA |= (1 << ISC00);
    EICRA &= ~((1 << ISC01));

    EIMSK |= (1 << INT0);
}

ISR(INT0_vect)
{
    static uint8_t button_state = 0;

    if (debounce_lock)
        return;

    debounce_start();

    if (button_state == 0)
    {
        button_state = 1; // PRESS event

        PORTB ^= (1 << PB0); // action on press
    }
    else
    {
        button_state = 0; // RELEASE event
    }
}

ISR(TIMER1_COMPA_vect)
{
    debounce_lock = 0;

    TIMSK1 &= ~(1 << OCIE1A); // stop timer interrupt
}

int main()
{
    DDRB |= (1 << PB0);

    timer1_init();
    int0_init();

    sei();

    while (1);
}