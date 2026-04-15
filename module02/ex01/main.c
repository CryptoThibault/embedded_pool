#include <avr/io.h>

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

void wdt_disable_early() __attribute__((naked)) __attribute__((section(".init3"))); 
// Place this function in the .init3 section so it runs before main(), without prologue/epilogue

void wdt_disable_early()
{
    MCUSR = 0; // Clear reset flags (important after watchdog reset to avoid misbehavior)

    WDTCSR = (1 << WDCE) | (1 << WDE); // Enable timed window to modify WDT (must be done before changing configuration)

    WDTCSR = 0x00; // Disable watchdog completely to prevent immediate reset loop
}

void wdt_init()
{
    MCUSR = 0; // Clear reset flags
    
    WDTCSR = (1 << WDCE) | (1 << WDE); // Enable change
    
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0); // Set prescaler for ~2s + enable reset
}

int main()
{
    uart_init();

    uart_printstr("Hello World!\n\r");

    wdt_init(); // Watchdog Timer

    while(1);
}