#include "main.h"

void uart_init(void)
{
    uint16_t ubrr = F_CPU / (8UL * UART_BAUDRATE) - 1; // Set baud rate value for 115200 (with double speed and 16MHz clock)
    UCSR0A |= (1 << U2X0); // Enable double speed mode to improve baud rate accuracy
    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register
    UBRR0L = ubrr;        // Set low byte of baud rate register
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable UART receiver and transmitter, and receiver interrupts
    // RXCIE0 is RX Complete Interrupt Enable

    uart_display_main_menu();
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

void uart_print_hex8(uint8_t val)
{
    const char hex[] = "0123456789abcdef";
    uart_tx(hex[val >> 4]);
    uart_tx(hex[val & 0x0F]);
}

__attribute__((signal, used))
void USART_RX_vect(void) {
    uart_update_menu(uart_rx());
}