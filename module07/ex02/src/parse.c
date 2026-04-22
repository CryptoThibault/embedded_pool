#include "main.h"

char *next_token(char **s)
{
    char *start;
    char *end;

    if (!s || !*s) return NULL;

    start = *s;
    while (*start == ' ' || *start == '\t')
        start++;

    if (*start == '\0')
    {
        *s = start;
        return NULL;
    }

    end = start;
    while (*end && *end != ' ' && *end != '\t')
        end++;

    if (*end)
    {
        *end = '\0';
        *s = end + 1;
    }
    else
    {
        *s = end;
    }

    return start;
}

uint8_t parse_u32(const char *s, uint32_t *out)
{
    uint32_t val = 0;

    if (!s || !out || *s == '\0') return 0;

    while (*s)
    {
        if (*s < '0' || *s > '9')
            return 0;

        if (val > (UINT32_MAX - (*s - '0')) / 10)
            return 0;

        val = val * 10 + (*s - '0');
        s++;
    }

    *out = val;
    return 1;
}

uint8_t parse_i16(const char *s, int16_t *out)
{
    uint32_t uval;
    int sign = 1;

    if (!s || !out || *s == '\0') return 0;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    if (!parse_u32(s, &uval))
        return 0;

    if (sign == 1 && uval > 32767)
        return 0;

    if (sign == -1 && uval > 32768)
        return 0;

    *out = (int16_t)(sign * (int32_t)uval);
    return 1;
}

uint8_t parse_tag(const char *in, char out[33])
{
    uint8_t i = 0;

    if (!in || *in != '"') return 0;

    in++;

    while (*in && *in != '"')
    {
        char c = *in++;

        if (i >= 32) return 0;

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
                || (c >= '0' && c <= '9') || c == '-' || c == '_')
            out[i++] = c;
        else
            return 0;
    }

    if (*in != '"')
        return 0;

    out[i] = '\0';
    return 1;
}