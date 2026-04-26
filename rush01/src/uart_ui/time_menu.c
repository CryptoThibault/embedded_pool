#include "main.h"

void uart_display_time_menu(void) {
    uart_printstr("Time configuration:\r\n");
    uart_printstr("   Please enter the new time, in format HH:MM:SS, then press enter\r\n");
    uart_printstr("> ");
}

bool parse_time_field(char *str, uint8_t *out_val) {
    if (str[0] < '0' || '9' < str[0])
        return false;
    if (str[1] < '0' || '9' < str[1])
        return false;
    *out_val = (str[0] - '0') * 10 + (str[1] - '0');
    return true;
}

bool parse_time(char str[8], t_time *time) {
    return (
        parse_time_field(str, &time->hours)
        && time->hours < 24
        && str[2] == ':'
        && parse_time_field(str + 3, &time->minutes)
        && time->minutes < 60
        && str[5] == ':'
        && parse_time_field(str + 6, &time->seconds)
        && time->seconds < 60
    );
}

void uart_update_time_menu(char c, t_uart_menu *current) {
    static char buf[8] = {0};
    static int pos = 0;
    t_time time;

    if (c == '\x7F' && pos) {
        uart_printstr("\x08 \x08");
        pos--;
        return;
    }
    if (pos == 8 && c == '\r' && parse_time(buf, &time)) {
        board.time = time;
        events |= EVENT_UART;
        pos = 0;
        *current = UART_MENU_MAIN;
        uart_clear_screen();
        uart_display_main_menu();
    }
    if (pos < 8 && (('0' <= c && c <= '9') || c == ':')) {
        uart_tx(c);
        buf[pos] = c;
        pos++;
    }
}