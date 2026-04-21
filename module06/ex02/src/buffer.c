#include "main.h"

void buffer_add(float *buf, uint8_t count, float new_value)
{
    if (count < 3)
    {
        buf[count] = new_value;
    }
    else
    {
        buf[0] = buf[1];
        buf[1] = buf[2];
        buf[2] = new_value;
    }
}

float buffer_avg(float *buf, uint8_t count)
{
    float sum = 0;

    for (uint8_t i = 0; i < count; i++)
        sum += buf[i];

    return sum / count;
}