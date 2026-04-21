#pragma once
#include <avr/io.h>
#include <avr/eeprom.h>

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char* str);
void uart_print_hex8(uint8_t val);
void uart_print_hex16(uint16_t val);

void eeprom_hexdump(void);