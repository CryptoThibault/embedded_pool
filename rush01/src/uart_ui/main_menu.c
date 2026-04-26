#include "main.h"

void uart_display_main_menu(void) {
    uart_printstr("Menu:\r\n");
    uart_printstr("[ ] configure time (seconds, hours, minutes)\r\n");
    uart_printstr("[ ] configure date (day, month, year)\r\n");
    uart_printstr("(use arrows to move around, and enter to select)\r\n");
    uart_printstr("\e[2;2Hx\e[2;2H");
}

void uart_update_main_menu(char c, t_uart_menu *current) {
    static int cursor = 0;

    t_uart_arrow dir = uart_handle_arrows(c);
    if (dir != UART_ARROW_NONE) {
        switch (dir) {
            case UART_ARROW_UP:
                cursor = (cursor + 1) % 2;
                break;
            case UART_ARROW_DOWN:
                cursor = (cursor + 1) % 2;
                break;
        }
        uart_tx(' ');
        uart_set_pos(2 + cursor, 2);
        uart_tx('x');
        uart_set_pos(2 + cursor, 2);
        return;
    }
    if (c == '\r') {
        *current = cursor + 1;
        uart_clear_screen();
        uart_display_menu(*current);
    }
}

void uart_display_menu(t_uart_menu menu) {
    switch (menu) {
        case UART_MENU_MAIN:
            uart_display_main_menu();
            break;
        case UART_MENU_TIME:
            uart_display_time_menu();
            break;
        case UART_MENU_DATE:
            uart_display_date_menu();
            break;
    }
}

void uart_update_menu(char c) {
    static t_uart_menu current;

    switch (current) {
        case UART_MENU_MAIN:
            uart_update_main_menu(c, &current);
            break;
        case UART_MENU_TIME:
            uart_update_time_menu(c, &current);
            break;
        case UART_MENU_DATE:
            uart_update_date_menu(c, &current);
            break;
    }
}
