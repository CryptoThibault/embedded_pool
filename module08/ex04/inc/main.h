#pragma once
#include <avr/io.h>

#define BUFFER_SIZE 12

typedef struct s_led
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} t_led;

extern t_led leds[3];

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
void spi_start(void);
void spi_stop(void);
void spi_set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t br);

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);
uint8_t uart_line_process(char *buff, uint8_t *i);

void update_rgb(void);
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void wheel(uint8_t pos);

void timer1_start(void);
void timer1_stop(void);

uint8_t str_equal(const char *s1, const char *s2);

uint8_t is_hex(char c);
uint8_t hex_to_u8(const char *s, uint8_t *out);

uint8_t parse_cmd(const char *buf, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *led);