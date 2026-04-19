#pragma once
#include <avr/io.h>
#include <util/delay.h>

void adc_init(void);
uint16_t adc_read(void);

void init_rgb();
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void wheel(uint8_t pos);
