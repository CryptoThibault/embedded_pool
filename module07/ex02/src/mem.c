#include "main.h"

int mem_cmp(const void *a, const void *b, uint16_t size)
{
    const uint8_t *p1 = (const uint8_t *)a;
    const uint8_t *p2 = (const uint8_t *)b;

    for (uint16_t i = 0; i < size; i++)
    {
        if (p1[i] != p2[i])
            return (p1[i] - p2[i]);
    }

    return 0;
}