#pragma once
#include <avr/io.h>

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char* str);
void uart_print_hex8(uint8_t val);

void adc_init(void);
uint16_t adc_read(void);

void timer1_init(void);
void TIMER1_COMPA_vect(void);