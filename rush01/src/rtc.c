#include "main.h"

void rtc_write(uint8_t buf[9])
{
    i2c_start();
    i2c_write(RTC_ADDR << 1 | TW_WRITE);
    i2c_write(0x00);
    for (uint8_t i = 0; i < 9; i++)
        i2c_write(buf[i]);
    i2c_stop();
}

void rtc_read(uint8_t buf[9])
{
    i2c_start();
    i2c_write(RTC_ADDR << 1 | TW_WRITE);
    i2c_write(0x00);
    i2c_stop();
    i2c_start();
    i2c_write(RTC_ADDR << 1 | TW_READ);
    for (uint8_t i = 0; i < 8; i++)
        buf[i] = i2c_read_ack();
    buf[8] = i2c_read_nack();
    i2c_stop();
}

void rtc_configure(void)
{
    char buf[9];

    rtc_read(buf);    
    buf[2] = (board.time.seconds / 10 << 4) + board.time.seconds % 10;
    buf[3] = (board.time.minutes / 10 << 4) + board.time.minutes % 10;
    buf[4] = (board.time.hours / 10 << 4) + board.time.hours % 10;
    buf[5] = (board.date.day / 10 << 4) + board.date.day % 10;
    buf[7] = (board.date.month / 10 << 4) + board.date.month % 10;
    buf[8] = ((board.date.year % 100) / 10 << 4) + (board.date.year % 100) % 10;
    rtc_write(buf);
}

void rtc_update(void)
{
    static uint32_t last = 0;
    char buf[9];

    if (ms - last < 1000) return;

    rtc_read(buf);
    board.time.seconds = ((buf[2] & 0x70) >> 4) * 10 + (buf[2] & 0xF);
    board.time.minutes = ((buf[3] & 0x70) >> 4) * 10 + (buf[3] & 0xF);
    board.time.hours = ((buf[4] & 0x30) >> 4) * 10 + (buf[4] & 0xF);
    board.date.day = ((buf[5] & 0x30) >> 4) * 10 + (buf[5] & 0xF);
    board.date.month = ((buf[7] & 0x10) >> 4) * 10 + (buf[7] & 0xF);
    board.date.year = 2000 + ((buf[8] & 0xF0) >> 4) * 10 + (buf[8] & 0xF);

    last = ms;
}