#include <avr/io.h>

int main()
{
    uint8_t duty = 10;

    DDRB |= (1 << PB1); // set PB1 (OC1A) as output pin for LED

    TCCR1A = (1 << COM1A1) | (1 << WGM11); // PWM non-inverting on OC1A + mode 14 (part 1)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // mode 14 (part 2) + prescaler 1024

    ICR1 = F_CPU / 1024UL - 1; // TOP value → sets PWM period (timer counts to ICR1)
    OCR1A = (uint32_t)ICR1 * duty / 100; // duty cycle → ON time proportional to ICR1

    TCCR1B |= (1 << CS12) | (1 << CS10); // start timer with prescaler 1024

    while (1); // empty loop, all PWM generation handled by hardware
}