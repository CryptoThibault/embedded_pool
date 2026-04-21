#pragma once
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

// #define I2C_DEBUG

#define AHT20_ADDR         0x38
#define AHT20_CMD_TRIGGER  0xAC
#define AHT20_CMD_ARG1     0x33
#define AHT20_CMD_ARG2     0x00

#ifdef I2C_DEBUG
#define I2C_LOG() i2c_status()
#else
#define I2C_LOG()
#endif

extern volatile uint8_t buf[7];

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char* str);
void uart_print_hex8(uint8_t val);
void uart_print_int(int value);
void uart_print_float(float value);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_status(void);
void i2c_write(unsigned char data);
void i2c_read(void);
void ath20_read(void);

void buffer_add(float *buf, uint8_t count, float new_value);
float buffer_avg(float *buf, uint8_t count);