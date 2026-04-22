#include "main.h"

void uart_init(void)
{
    uint16_t ubrr = F_CPU / (8UL * UART_BAUDRATE) - 1; // Set baud rate value for 115200 (with double speed and 16MHz clock)
    UCSR0A |= (1 << U2X0); // Enable double speed mode to improve baud rate accuracy
    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register
    UBRR0L = ubrr;        // Set low byte of baud rate register
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Enable UART transmitter and receiver (TX and RX hardware active, allows sending and receiving data)
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until transmit buffer is empty and ready
    UDR0 = c; // Load character into UART data register to start transmission
}

char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0))); // Wait until data received
    return UDR0; // Read received byte
}

void uart_printstr(const char* str)
{
    while (*str) uart_tx(*str++);
}

uint8_t uart_line_process(char *buf, uint8_t *i)
{
    char c = uart_rx();

    if (c == '\r')
    {
        buf[*i] = '\0';
        *i = 0;

        uart_tx('\r');
        uart_tx('\n');

        return 1;
    }
    else if (c == '\b' || c == 0x7F)
    {
        if (*i > 0)
        {
            (*i)--;
            buf[*i] = '\0';

            uart_tx('\b');
            uart_tx(' ');
            uart_tx('\b');
        }
    }
    else
    {
        if (*i < BUFFER_SIZE - 1)
        {
            buf[(*i)++] = c;
            uart_tx(c);
        }
    }

    return 0;
}

void uart_print_uint32(uint32_t val)
{
    char buf[11];
    uint8_t i = 0;

    if (val == 0)
    {
        uart_tx('0');
        return;
    }

    while (val > 0)
    {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    }

    while (i > 0)
    {
        uart_tx(buf[--i]);
    }
}

void uart_print_int16(int16_t val)
{
    if (val < 0)
    {
        uart_tx('-');
        uart_print_uint32((uint16_t)(-val));
    }
    else
    {
        uart_print_uint32((uint16_t)val);
    }
}