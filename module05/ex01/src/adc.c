#include "main.h"

void adc_init(void)
{
    ADMUX = (1 << REFS0) | (1 << ADLAR); // AVcc reference (5V) + 8-bit result
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enable ADC (prescaler 128)
}

uint16_t adc_read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // select ADC0–ADC7

    ADCSRA |= (1 << ADSC); // conversion
    while (ADCSRA & (1 << ADSC));
    return ADCH;
}