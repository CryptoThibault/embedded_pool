#include <avr/io.h>
#include <avr/interrupt.h>

#define DEBOUNCE_MS 30

volatile uint8_t value = 0;
volatile uint8_t debounce_lock = 0;

void timer1_init(void)
{
    TCCR1A = 0;

    TCCR1B = (1 << CS11) | (1 << CS10); // prescaler 64 → 1 tick = 4 µs (16 MHz clock)
    TCCR1B &= ~(1 << WGM12); // normal mode

    TIMSK1 &= ~(1 << OCIE1A); // disable interrupt initially
}

void TIMER1_COMPA_vect(void) __attribute__((signal));

void TIMER1_COMPA_vect(void)
{
    debounce_lock = 0;

    TIMSK1 &= ~(1 << OCIE1A); // stop timer interrupt
}

void debounce_start(void)
{
    debounce_lock = 1;

    TCNT1 = 0;
    
    OCR1A = (DEBOUNCE_MS * 1000UL) / 4; // 30ms / 4µs = 7500 ticks

    TIFR1 |= (1 << OCF1A);     // clear flag
    TIMSK1 |= (1 << OCIE1A);   // enable compare interrupt
}

void displayBinary(uint8_t v)
{
    PORTB &= ~((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4)); // clear LED pins (PB0,PB1,PB2,PB4)

    PORTB |= (v & 1) << PB0;        // bit0 -> PB0
    PORTB |= ((v >> 1) & 1) << PB1; // bit1 -> PB1
    PORTB |= ((v >> 2) & 1) << PB2; // bit2 -> PB2
    PORTB |= ((v >> 3) & 1) << PB4; // bit3 -> PB4
}

void int0_init(void)
{
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    // interrupt on ANY logical change (press + release)
    EICRA |= (1 << ISC00);
    EICRA &= ~((1 << ISC01));

    EIMSK |= (1 << INT0);
}

void INT0_vect(void) __attribute__((signal, used));

void INT0_vect(void)
{
    static uint8_t button_state = 0;

    if (debounce_lock)
        return;

    debounce_start();

    if (button_state == 0)
    {
        button_state = 1;// PRESS event

        if (value < 15) value++;
        displayBinary(value);
    }
    else
    {
        button_state = 0; // RELEASE event
    }
}

void pcint2_init(void)
{
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD4);

    PCICR |= (1 << PCIE2);      // enable interrupt group for PORTD
    PCMSK2 |= (1 << PCINT20);   // enable PD4 interrupt
}

void PCINT2_vect(void) __attribute__((signal, used));

void PCINT2_vect(void)
{
    static uint8_t button_state = 0;

    if (debounce_lock)
        return;

    debounce_start();

    if (button_state == 0)
    {
        button_state = 1; // PRESS event

        if (value > 0) value--;
        displayBinary(value);
    }
    else
    {
        button_state = 0; // RELEASE event
    }
}

int main(void)
{
    DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4);

    timer1_init();
    int0_init();
    pcint2_init();

    SREG |= (1 << 7); // sei()

    while (1);
}