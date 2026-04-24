#include "main.h"

uint8_t parse_cmd(const char *buf, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *led)
{
    for (int i = 0; i < 8; i++)
        if (buf[i] == '\0') return 0;
    if (buf[8] != '\0') return 0;

    for (int i = 0; i < 6; i++)
        if (!is_hex(buf[i])) return 0;

    if (!hex_to_u8(&buf[0], r)) return 0;
    if (!hex_to_u8(&buf[2], g)) return 0;
    if (!hex_to_u8(&buf[4], b)) return 0;

    if (buf[6] != 'D') return 0;

    if (buf[7] == '6') *led = 0;
    else if (buf[7] == '7') *led = 1;
    else if (buf[7] == '8') *led = 2;
    else return 0;

    return 1;
}