#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init()
{
    uint16_t ubrr = F_CPU / (8UL * UART_BAUDRATE) - 1; // Set baud rate value for 115200 (with double speed and 16MHz clock)

    UCSR0A |= (1 << U2X0); // Enable double speed mode to improve baud rate accuracy

    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register
    UBRR0L = ubrr;        // Set low byte of baud rate register

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configure frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0B = (1 << TXEN0); // Enable UART transmitter (TX hardware active, allows sending data)
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until transmit buffer is empty and ready

    UDR0 = c; // Load character into UART data register to start transmission
}

void uart_printstr(const char* str)
{
    while (*str)
    {
        uart_tx(*str);
        str++;
    }
}

void timer1_init(void)
{
    TCCR1A = 0;                               // mode normal
    TCCR1B = (1 << WGM12);                    // CTC mode

    TCCR1B |= (1 << CS12) | (1 << CS10);      // prescaler 1024

    OCR1A = F_CPU / 1024UL * 2;               // 2000 toggle

    TIMSK1 |= (1 << OCIE1A);                  // enable interrupt
}

void TIMER1_COMPA_vect(void) __attribute__((signal));

void TIMER1_COMPA_vect(void)
{
    uart_printstr("Hello World!\n\r");
}

int main()
{
    uart_init();
    timer1_init();

    SREG |= (1 << 7); // sei()

    while(1);
}