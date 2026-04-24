#include "main.h"

uint8_t is_hex(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

uint8_t hex_to_u8(const char *s, uint8_t *out)
{
    uint8_t val = 0;

    for (int i = 0; i < 2; i++)
    {
        char c = s[i];
        uint8_t v;

        if (c >= '0' && c <= '9') v = c - '0';
        else if (c >= 'A' && c <= 'F') v = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') v = c - 'a' + 10;
        else return 0;

        val = (val << 4) | v;
    }

    *out = val;
    return 1;
}