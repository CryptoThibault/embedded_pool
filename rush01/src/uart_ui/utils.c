#include "main.h"

void uart_putbyte(unsigned char c) {
    char *digits = "0123456789ABCDEF";

    uart_tx('0');
    uart_tx('x');
    uart_tx(digits[c / 16 % 16]);
    uart_tx(digits[c % 16]);
}

t_uart_arrow uart_handle_arrows(char c) {
    const char arrow_sequence[2] = "\x1B\x5B";
    static int arrow_index = 0;

    if (arrow_index == sizeof(arrow_sequence)) {
        arrow_index = 0;
        if ('A' <= c && c <= 'D')
            return c - 'A' + 2;
    } else if (c == arrow_sequence[arrow_index]) {
        arrow_index++;
        return UART_ARROW_READING;
    }
    arrow_index = 0;
    return UART_ARROW_NONE;
}

void uart_putnbr(unsigned int n) {
    if (n >= 10)
        uart_putnbr(n / 10);
    uart_tx(n % 10 + '0');
}

void uart_set_pos(unsigned int x, unsigned int y) {
    uart_printstr("\e[");
    uart_putnbr(x);
    uart_tx(';');
    uart_putnbr(y);
    uart_tx('H');
}

void uart_clear_screen(void) {
    uart_printstr("\e[2J]\e[1;1H");
}
