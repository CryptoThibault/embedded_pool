#include "main.h"

void uart_display_date_menu(void) {
    uart_printstr("Date configuration:\r\n");
    uart_printstr("   Please enter the new date, in format DD/MM/20YY, then press enter\r\n");
    uart_printstr("> ");
}

bool parse_date_field(char *str, uint8_t *out_val) {
    if (str[0] < '0' || '9' < str[0])
        return false;
    if (str[1] < '0' || '9' < str[1])
        return false;
    *out_val = (str[0] - '0') * 10 + (str[1] - '0');
    return true;
}

bool parse_year_field(char *str, uint16_t *out_val) {
    uint8_t century;
    uint8_t year;

    if (!parse_date_field(str, &century) || !parse_date_field(str + 2, &year))
        return false;
    *out_val = (uint16_t) century * 100 + year;
    return true;
}

bool parse_date(char str[10], t_date *date) {
    return (
        parse_date_field(str, &date->day)
        // Todo: take into account month durations and leap days
        && 1 <= date->day && date->day <= 31
        && str[2] == '/'
        && parse_date_field(str + 3, &date->month)
        && 1 <= date->month && date->month <= 12
        && str[5] == '/'
        && parse_year_field(str + 6, &date->year)
        && 2000 <= date->year && date->year <= 2099
        // Todo: add limits on year
    );
}

void uart_update_date_menu(char c, t_uart_menu *current) {
    static char buf[10] = {0};
    static int pos = 0;
    t_date date;

    if (c == '\x7F' && pos) {
        uart_printstr("\x08 \x08");
        pos--;
        return;
    }
    if (pos == 10 && c == '\r' && parse_date(buf, &date)) {
        board.date = date;
        events |= EVENT_UART;
        pos = 0;
        *current = UART_MENU_MAIN;
        uart_clear_screen();
        uart_display_main_menu();
    }
    if (pos < 10 && (('0' <= c && c <= '9') || c == '/')) {
        uart_tx(c);
        buf[pos] = c;
        pos++;
    }
}