#include "main.h"

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