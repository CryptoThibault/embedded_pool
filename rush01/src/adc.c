#include "main.h"

void adc_init(void)
{
    ADMUX = (1 << REFS0); // AVcc reference (5V)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enable ADC (prescaler 128)
}

uint16_t adc_read(uint8_t channel)
{
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    if (channel <= 7)
        ADMUX = (1 << REFS0) | (channel & 0x0F);
    else if (channel == 8)
        ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADC;
}