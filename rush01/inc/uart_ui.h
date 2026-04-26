#pragma once
#include <stdbool.h>

typedef enum {
    UART_ARROW_NONE    = 0,
    UART_ARROW_READING = 1,
    UART_ARROW_UP      = 2,
    UART_ARROW_DOWN    = 3,
    UART_ARROW_RIGHT   = 4,
    UART_ARROW_LEFT    = 5,
}   t_uart_arrow;

void uart_putbyte(unsigned char c);
t_uart_arrow uart_handle_arrows(char c);
void uart_putnbr(unsigned int n);
void uart_set_pos(unsigned int x, unsigned int y);
void uart_clear_screen(void);

typedef enum {
    UART_MENU_MAIN,
    UART_MENU_TIME,
    UART_MENU_DATE,
    UART_MENU_YEAR,
}   t_uart_menu;

void uart_display_main_menu(void);
void uart_display_menu(t_uart_menu menu);
void uart_update_menu(char c);
void uart_display_time_menu(void);
void uart_update_time_menu(char c, t_uart_menu *current);
void uart_display_date_menu(void);
void uart_update_date_menu(char c, t_uart_menu *current);
