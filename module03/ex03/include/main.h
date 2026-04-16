#pragma once
#include <avr/io.h>
#include <util/delay.h>

void uart_init();
void uart_tx(char c);
char uart_rx();
void uart_printstr(const char* str);
uint8_t uart_line_process(char *buff, uint8_t *i);

void init_rgb();
void disable_rgb();
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void rgb_filter(uint8_t *rgb);

uint8_t is_hex_string(const char *str);
uint8_t hex_to_nibble(char c);
uint8_t hex_to_byte(char high, char low);
void hex_to_rgb(const char *str, uint8_t *rgb);