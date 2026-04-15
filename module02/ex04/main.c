#include <avr/io.h>
#include <util/delay.h>

void uart_init()
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

char uart_rx()
{
    while (!(UCSR0A & (1 << RXC0))); // wait until data received

    return UDR0; // read received byte
}

void uart_printstr(const char* str)
{
    while (*str)
    {
        uart_tx(*str);
        str++;
    }
}

uint8_t uart_line_process(char *buff, uint8_t *i, uint8_t hide)
{
    char c = uart_rx();

    if (c == '\r')
    {
        buff[*i] = '\0';
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
            buff[*i] = '\0';

            uart_tx('\b');
            uart_tx(' ');
            uart_tx('\b');
        }
    }
    else
    {
        if (*i < 31)
        {
            buff[(*i)++] = c;
            uart_tx(hide ? '*' : c);
        }
    }

    return 0;
}

int strcmp(const char *a, const char *b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

void blink_led(uint8_t pin, int tick, int ratio)
{
    if (tick % ratio == 0)
        PORTB ^= (1 << pin);
}

int main()
{
    char* username = "pisciner";
    char* password = "Code42!";

    uart_init();

    while (1)
    {
        char user[32];
        char pass[32];
        uint8_t i = 0;

        uart_printstr("Enter your login:\n\r");

        uart_printstr("    username: ");
        while (1)
            if (uart_line_process(user, &i, 0)) break;

        uart_printstr("    password: ");
        while (1)
            if (uart_line_process(pass, &i, 1)) break;

        if (!strcmp(user, username) && !strcmp(pass, password))
        {
            uart_printstr("Hello ");
            uart_printstr(user);
            uart_printstr("!\n\rShall we play a game?\n\r");

            DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4);

            while(1)
            {
                blink_led(PB0, i, 4);
                blink_led(PB1, i, 8);
                blink_led(PB2, i, 16);
                blink_led(PB4, i, 32);

                i++;
                if (i > 64) i = 0;

                _delay_ms(10);
            }
        }
        else
        {
            uart_printstr("Bad combinaison username/password\n\n\r");
        }
    }
}