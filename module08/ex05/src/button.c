#include "main.h"

void int0_init(void)
{
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
    EICRA |= (1 << ISC00);
    EICRA &= ~((1 << ISC01));
    EIMSK |= (1 << INT0);
}

void int0_event(void)
{
    if (color == 0) leds[id].r = adc_read();
    if (color == 1) leds[id].g = adc_read();
    if (color == 2) leds[id].b = adc_read();
    update_rgb();
    if (++color > 2) color = 0;
}

__attribute__((signal, used))
void INT0_vect(void)
{
    static uint8_t button_state = 0;

    if (debounce_lock) return;

    debounce_start();

    if (button_state == 0)
    {
        button_state = 1;// PRESS event
    
        events |= EVENT_BTN1;
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
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT20);
}

void pcint2_event(void)
{
    if (++id > 2) id = 0;
    blink_led(id);
}

__attribute__((signal, used))
void PCINT2_vect(void)
{
    static uint8_t button_state = 0;

    if (debounce_lock)
        return;

    debounce_start();

    if (button_state == 0)
    {
        button_state = 1; // PRESS event
        
        events |= EVENT_BTN2;
    }
    else
    {
        button_state = 0; // RELEASE event
    }
}