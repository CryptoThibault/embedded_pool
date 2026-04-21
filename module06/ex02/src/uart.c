#include "main.h"

void uart_init(void)
{
    uint16_t ubrr = F_CPU / (8UL * UART_BAUDRATE) - 1; // Set baud rate value for 115200 (with double speed and 16MHz clock)
    UCSR0A |= (1 << U2X0); // Enable double speed mode to improve baud rate accuracy
    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register
    UBRR0L = ubrr;        // Set low byte of baud rate register
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0B = (1 << TXEN0); // Enable UART transmitter (TX pin active)
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until transmit buffer is empty and ready
    UDR0 = c; // Load character into UART data register to start transmission
}

void uart_printstr(const char* str)
{
    while (*str) uart_tx(*str++);
}

void uart_print_hex8(uint8_t val)
{
    const char hex[] = "0123456789ABCDEF";

    uart_tx(hex[val >> 4]);
    uart_tx(hex[val & 0x0F]);
}

void uart_print_int(int value)
{
    char buffer[10];
    int i = 0;

    if (value == 0)
    {
        uart_tx('0');
        return;
    }

    if (value < 0)
    {
        uart_tx('-');
        value = -value;
    }

    while (value > 0)
    {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    while (i--)
        uart_tx(buffer[i]);
}

void uart_print_float(float value)
{
    int int_part = (int)value;
    int dec_part = (int)((value - int_part) * 10);

    uart_print_int(int_part);
    uart_tx(',');

    if (dec_part < 0)
        dec_part = -dec_part;

    uart_print_int(dec_part);
}