#pragma once
#include <avr/io.h>
#include <util/delay.h>

#define EXP_ADDR  0x20
#define EXP_PORT0 0x06

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_status(void);
void i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);

void exp_init(void);
void exp_display_binary(uint8_t val);
uint8_t exp_read_gpio(void);