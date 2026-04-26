#include "main.h"

void update_startup(void)
{
    seg_display(0xFF);
    seg_select(0x0);
    led_display_binary(15);
    while (!board.running && ms <= 3000);
    seg_select(0xF);
    led_display_binary(0);
    while (!board.running && ms <= 4000);
    board.running = 1;
}

void update_modes(void)
{
    switch (board.mode)
    {
        case 0:
        case 1:
        case 2:
            if (events & EVENT_TIMER)
                board.value = adc_read(board.mode);
            break;
        case 3:
            if (events & EVENT_TIMER)
                board.value = adc_read(8);
            break;
        case 4:
            rgb_display();
            break;
        case 5:
            aht20_measure();
            board.value = board.temp_c;
            break;
        case 6:
            aht20_measure();
            board.value = board.temp_f;
            break;
        case 7:
            aht20_measure();
            board.value = board.hum;
            break;
        case 8:
            rtc_update();
            board.value = board.time.hours * 100 + board.time.minutes;
            break;
        case 9:
            rtc_update();
            board.value = board.date.day * 100 + board.date.month;
            break;
        case 10:
            rtc_update();
            board.value = board.date.year;
            break;
    }
}

void update_events(void)
{
    if (events & EVENT_TIMER)
    {
        events &= ~EVENT_TIMER;
        if (board.mode == 4)
            seg_print_42();
        else if (board.mode < 8)
            seg_print_value();
        else
            seg_print_time();
    }

    if (events & EVENT_BTN1)
    {
        events &= ~EVENT_BTN1;
        event_btn1();
    }
    if (events & EVENT_BTN2)
    {
        events &= ~EVENT_BTN2;
        event_btn2();
    }
    if (events & EVENT_BTN3)
    {
        events &= ~EVENT_BTN3;
        event_btn3();
    }

    if (events & EVENT_UART)
    {
        events &= ~EVENT_UART;
        rtc_configure();
        // uart_update_menu(uart_rx());
        // uart_set_pos(1, 10);
        // uart_printstr("here\r\n");
    }
}