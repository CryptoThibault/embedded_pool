#pragma once
#include <avr/io.h>
#include <avr/eeprom.h>

#define BUFFER_SIZE 7

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);
uint8_t uart_line_process(char *buf, uint8_t *i);
void uart_print_hex8(uint8_t val);
void uart_print_hex16(uint16_t val);

void eeprom_hexdump(uint16_t addr);

uint8_t is_hex(char c);
uint8_t hex_to_val(char c);