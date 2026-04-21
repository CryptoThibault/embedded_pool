#pragma once
#include <avr/io.h>
#include <util/twi.h>

#define I2C_DEBUG

#ifdef I2C_DEBUG
#define I2C_LOG() i2c_status()
#else
#define I2C_LOG()
#endif

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char* str);
void uart_print_hex8(uint8_t val);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_status(void);