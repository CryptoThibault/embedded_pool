#include <avr/io.h>

void uart_init()
{
    uint16_t ubrr = F_CPU / (8UL * UART_BAUDRATE) - 1; // Set baud rate value for 115200 (with double speed and 16MHz clock)

    UCSR0A |= (1 << U2X0); // Enable double speed mode to improve baud rate accuracy

    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register
    UBRR0L = ubrr;        // Set low byte of baud rate register

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure frame format: 8 data bits, no parity, 1 stop bit (8N1)
    // Enable UART transmitter, receiver and interupt (TX and RX hardware active, allows sending and receiving data)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until transmit buffer is empty and ready

    UDR0 = c; // Load character into UART data register to start transmission
}

char uart_rx()
{
    while (!(UCSR0A & (1 << RXC0))); // wait until data received

    return UDR0; // read received byte
}

void USART_RX_vect(void) __attribute__((signal, used));

void USART_RX_vect(void)
{
    char c = uart_rx();

    if (c >= 65 && c <= 90) c += 32;
    else if (c >= 97 && c <= 122) c -= 32;

    uart_tx(c);
}

int main()
{
    uart_init();

    SREG |= (1 << 7); // sei()

    while (1);
}