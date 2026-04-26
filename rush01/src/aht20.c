#include "main.h"

void aht20_write(void)
{
    i2c_start();
    i2c_write(AHT20_ADDR << 1 | TW_WRITE);
    i2c_write(AHT20_CMD_TRIGGER);
    i2c_write(AHT20_CMD_ARG1);
    i2c_write(AHT20_CMD_ARG2);
    i2c_stop();
}

void aht20_read(uint8_t buf[7])
{
    i2c_start();
    i2c_write(AHT20_ADDR << 1 | TW_READ);
    for (uint8_t i = 0; i < 6; i++)
        buf[i] = i2c_read_ack();
    buf[6] = i2c_read_nack();
    i2c_stop();
}

void aht20_measure(void)
{
    static uint32_t last = 0;
    static uint8_t read = 0;
    uint8_t buf[7];

    if (!read && ms - last >= 500)
    {
        last = ms;
        read = 1;
        aht20_write();
    }
    else if (read && ms - last >= 80)
    {
        last = ms;
        read = 0;
        aht20_read(buf);

        uint32_t temp_raw = ((uint32_t)(buf[3] & 0x0F) << 16) | ((uint32_t)buf[4] << 8) | (buf[5]);
        float temp_c   = (temp_raw * 200.0f / 1048576.0f) - 50.0f;
        float temp_f   = (temp_c * 9.0f / 5.0f) + 32.0f;
        uint32_t hum_raw = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] << 4)  | (buf[3] >> 4);
        float humidity = (hum_raw * 100.0f) / 1048576.0f;

        board.temp_c = (uint16_t)(temp_c * 10);
        board.temp_f = (uint16_t)(temp_f * 10);
        board.hum = (uint16_t)(humidity * 10);
    }
}