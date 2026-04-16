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

uint8_t uart_line_process(char *buff, uint8_t *i)
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
        if (*i < 6)
        {
            buff[(*i)++] = c;
            uart_tx(c);
        }
    }

    return 0;
}

void init_rgb()
{
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD3); // Set PD5 (red), PD6 (green), PD3 (blue) as output pins

    // RED + GREEN (Timer0)
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1); // Fast PWM mode + enable OC0A (green) and OC0B (red)
    TCCR0B = (1 << CS01) | (1 << CS00); // Set prescaler to 64 for Timer0 speed

    // BLUE (Timer2)
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1); // Fast PWM mode + enable OC2B (blue output)
    TCCR2B = (1 << CS22); // Set prescaler to 64 for Timer2 speed
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r; // Red brightness (0 = off, 255 = max)
    OCR0A = g; // Green brightness (0 = off, 255 = max)
    OCR2B = b; // Blue brightness (0 = off, 255 = max)
}

uint8_t is_hex_string(const char *str)
{
    uint8_t i = 0;

    while (str[i] != '\0')
    {
        char c = str[i];

        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))
            return 0;

        i++;
    }

    return (i == 6);
}

uint8_t hex_to_nibble(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return 0; // should never happen if validated
}

uint8_t hex_to_byte(char high, char low)
{
    return (hex_to_nibble(high) << 4) | hex_to_nibble(low);
}

void hex_to_rgb(const char *str, uint8_t *rgb)
{
    rgb[0] = hex_to_byte(str[0], str[1]);
    rgb[1] = hex_to_byte(str[2], str[3]);
    rgb[2] = hex_to_byte(str[4], str[5]);
}

void rgb_filter(uint8_t *rgb)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (rgb[i] < 5)
            rgb[i] = 0;
        else
            rgb[i] = (rgb[i] * rgb[i]) / 255;
    }
}

int main()
{
    uint8_t filter = 0;

    uart_init();
    init_rgb();

    while (1)
    {
        uint8_t i = 0;
        char str[6];

        uart_printstr("Enter a HEX RGB color: \r\n    #");
        while (!uart_line_process(str, &i));

        if (is_hex_string(str))
        {
            uart_printstr("The color is displayed on the LED!\r\n\n");

            uint8_t rgb[3];
            hex_to_rgb(str, rgb);
            if (filter) rgb_filter(rgb);
            set_rgb(rgb[0], rgb[1], rgb[2]);
        }
        else
        {
            uart_printstr("Invalid color format, please try again\r\n\n");
        }
    }
}