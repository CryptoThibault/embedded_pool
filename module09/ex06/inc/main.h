#pragma once
#include <avr/io.h>
#include <util/delay.h>

#define EXP_ADDR  0x20
#define EXP_PORT0 0x06
#define EXP_PORT1 0x07

#define DGT_1 0b11101111
#define DGT_2 0b11011111
#define DGT_3 0b10111111
#define DGT_4 0b01111111

#define SEG_0 0b11000000
#define SEG_1 0b11111001
#define SEG_2 0b10100100
#define SEG_3 0b10110000
#define SEG_4 0b10011001
#define SEG_5 0b10010010
#define SEG_6 0b10000010
#define SEG_7 0b11111000
#define SEG_8 0b10000000
#define SEG_9 0b10010000

extern volatile uint16_t g_value;

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);

void exp_init(void);
uint8_t exp_read_gpio(void);

void seg_select(uint8_t digit);
void seg_display(uint8_t value);
void seg_write(uint8_t value, uint8_t digit);

void timer0_init(void);

void adc_init(void);
uint16_t adc_read(void);