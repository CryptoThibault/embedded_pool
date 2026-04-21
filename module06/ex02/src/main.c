#include "main.h"

volatile uint8_t buf[7];

int main()
{
    float humidity_buffer[3];
    float temperature_buffer[3];
    uint8_t count = 0;

    uart_init();
    i2c_init();

    while (1)
    {
        ath20_read();

        uint32_t raw_humidity = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] << 4) | (buf[3] >> 4);
        uint32_t raw_temperature = (((uint32_t)(buf[3] & 0x0F) << 16) | ((uint32_t)buf[4] << 8) | buf[5]);

        float humidity = raw_humidity * 100.0f / 1048576.0f;
        humidity = ((int)(humidity * 10 + 0.5f)) / 10.0f;

        float temperature = raw_temperature * 200.0f / 1048576.0f - 50.0f;
        temperature = ((int)(temperature * 10 + 0.5f)) / 10.0f;

        if (count < 3) count++;
        buffer_add(humidity_buffer, count, humidity);
        buffer_add(temperature_buffer, count, temperature);

        if (count == 3)
        {
            uart_printstr("Temperature: ");
            uart_print_int((int)buffer_avg(temperature_buffer, count));
            uart_printstr(".C, Humidity: ");
            uart_print_float(buffer_avg(humidity_buffer, count));
            uart_printstr("%\r\n");
        }

        _delay_ms(500);
    }
}
