#pragma once
#include <avr/io.h>
#include <util/delay.h>

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
void spi_start(void);
void spi_stop(void);
void spi_set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t br);

void adc_init(void);
uint16_t adc_read(void);

void set_led_0(void);
void set_led_33(uint8_t r, uint8_t g, uint8_t b);
void set_led_66(uint8_t r, uint8_t g, uint8_t b);
void set_led_100(uint8_t r, uint8_t g, uint8_t b);