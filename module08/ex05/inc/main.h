#pragma once
#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_MS 30

typedef struct s_led
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} t_led;

typedef enum
{
    EVENT_NONE    = 0,
    EVENT_BTN1    = 1 << 0,
    EVENT_BTN2    = 1 << 1
} event_t;

extern t_led leds[3];
extern volatile uint8_t events;
extern volatile uint8_t debounce_lock;
extern uint8_t color;
extern uint8_t id;

void spi_init(void);
uint8_t spi_transfer(uint8_t data);
void spi_start(void);
void spi_stop(void);
void spi_set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t br);

void update_rgb(void);

void set_led_D6(uint8_t r, uint8_t g, uint8_t b);
void set_led_D7(uint8_t r, uint8_t g, uint8_t b);
void set_led_D8(uint8_t r, uint8_t g, uint8_t b);
void blink_led(uint8_t id);

void timer0_init(void);
void debounce_start(void);

void int0_init(void);
void int0_event(void);
void pcint2_init(void);
void pcint2_event(void);

void adc_init(void);
uint16_t adc_read(void);