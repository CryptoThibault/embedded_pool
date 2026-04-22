#pragma once
#include <avr/io.h>
#include <avr/eeprom.h>

#define BUFFER_SIZE 43
#define SLOT_COUNT 4
#define SLOT_INVALID 0xFF

typedef struct __attribute__((packed)) s_node
{
    uint16_t magic_nb;
    uint32_t id;
    int16_t priority;
    char tag[33];
    uint8_t version;
    uint16_t integrity;
} t_node;

extern t_node node;
extern uint8_t slot;
extern uint8_t debug_fail_slot;

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);
uint8_t uart_line_process(char *buf, uint8_t *i);
void uart_print_uint32(uint32_t val);
void uart_print_int16(int16_t val);

char *next_token(char **s);
uint8_t parse_u32(const char *s, uint32_t *out);
uint8_t parse_i16(const char *s, int16_t *out);
uint8_t parse_tag(const char *in, char out[33]);

uint8_t str_equal(const char *s1, const char *s2);
char *str_cpy(char *dest, const char *src);

int mem_cmp(const void *a, const void *b, uint16_t size);

void eeprom_read_node(t_node *out);
void eeprom_write_node(const t_node *node);
void load_from_eeprom(void);

uint8_t is_valid_node(t_node *n);
uint16_t compute_integrity(const t_node *n);
uint8_t save_node(void);
void relocate_node(void);

void status(void);
void set_id(uint32_t id);
void set_prio(int16_t prio);
void set_tag(const char* tag);
void factory_reset(void);