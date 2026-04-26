#pragma once
#include <avr/io.h>
#include <util/delay.h>

#include "uart_ui.h"

#define DEBOUNCE_MS 30
#define BUFFER_SIZE 20

#define INTERUPT_ON SREG |= (1 << 7)

#define TW_WRITE 0
#define TW_READ  1

#define AHT20_ADDR          0x38
#define AHT20_CMD_TRIGGER   0xAC
#define AHT20_CMD_ARG1      0x33
#define AHT20_CMD_ARG2      0x00

#define EXP_ADDR            0x20
#define EXP_PORT0_OUT       0x02
#define EXP_PORT1_OUT       0x03
#define EXP_PORT0_DIR       0x06
#define EXP_PORT1_DIR       0x07

#define EXP_LED_D9_BIT      3
#define EXP_LED_D10_BIT     2
#define EXP_LED_D11_BIT     1

#define RTC_ADDR            0x51

#define DGT_1 0b1110
#define DGT_2 0b1101
#define DGT_3 0b1011
#define DGT_4 0b0111

#define SEG_0 0b00111111
#define SEG_1 0b00000110
#define SEG_2 0b01011011
#define SEG_3 0b01001111
#define SEG_4 0b01100110
#define SEG_5 0b01101101
#define SEG_6 0b01111101
#define SEG_7 0b00000111
#define SEG_8 0b01111111
#define SEG_9 0b01101111
#define SEG_D 0b01000000

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
} t_time;

typedef struct {
    uint8_t     day;
    uint8_t     month;
    uint16_t    year;
} t_date;

typedef struct s_board
{
    uint8_t running;
    uint8_t mode;
    uint16_t value;
    uint8_t exp_port0;
    uint16_t temp_c;
    uint16_t temp_f;
    uint16_t hum;
    t_time time;
    t_date date;
} t_board;

typedef enum
{
    EVENT_NONE  = 0,
    EVENT_TIMER = 1 << 0,
    EVENT_BTN1  = 1 << 1,
    EVENT_BTN2  = 1 << 2,
    EVENT_BTN3  = 1 << 3,
    EVENT_UART  = 1 << 4
} event_t;

extern volatile t_board board;
extern volatile uint8_t events;
extern volatile uint32_t ms;

void update_startup(void);
void update_modes(void);
void update_events(void);

void led_init(void);
void led_display_binary(uint8_t v);

void rgb_init(void);
void rgb_stop(void);
void rgb_display(void);

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);
void uart_print_hex8(uint8_t val);

void timer0_init(void);

void pcint_init(void);

void event_btn1(void);
void event_btn2(void);
void event_btn3(void);

void adc_init(void);
uint16_t adc_read(uint8_t channel);

void spi_init(void);
void spi_disable(void);
uint8_t spi_transfer(uint8_t data);
void spi_start(void);
void spi_stop(void);
void spi_set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t br);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);

void aht20_write(void);
void aht20_read(uint8_t buf[7]);
void aht20_measure(void);

void exp_init(void);

void seg_display(uint8_t value);
void seg_select(uint8_t digit);
void seg_write(uint8_t value, uint8_t digit);
void seg_print_value(void);
void seg_print_42(void);
void seg_print_time(void);

void rtc_write(uint8_t buf[9]);
void rtc_read(uint8_t buf[9]);
void rtc_configure(void);
void rtc_update(void);