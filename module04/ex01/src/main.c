#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init(void)
{
    TCCR0A = (1 << WGM01); // CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64

    OCR0A = 249; // 249 ticks = 1 ms

    TIMSK0 |= (1 << OCIE0A); // enable interrupt
}

void timer1_init(void)
{
    // Fast PWM 8-bit
    TCCR1A = (1 << WGM10) | (1 << COM1A1);
    TCCR1B = (1 << WGM12);
    
    TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64

    OCR1A = 0; // duty initial
}

void TIMER0_COMPA_vect(void) __attribute__((signal));

void TIMER0_COMPA_vect(void)
{
    static uint16_t acc = 0;
    static int8_t step = 1;

    acc += 256;

    if (acc >= 1000)
    {
        acc -= 1000;
    
        OCR1A += step;

        if (OCR1A == 0 || OCR1A == 255)
            step = -step;
    }
}

int main(void)
{
    DDRB |= (1 << PB1);

    timer0_init();
    timer1_init();

    SREG |= (1 << 7); // sei()

    while (1);
}