#include "main.h"

t_led leds[3];

int main(void)
{
    uart_init();
    spi_init();

    while (1)
    {
        char buf[BUFFER_SIZE];
        uint8_t i = 0;

        uart_tx('#');
        while (!uart_line_process(buf, &i));
        
        if (str_equal(buf , "FULLRAINBOW"))
        {
            timer1_start();
            continue;
        }

        uint8_t r, g, b, id;
        if (parse_cmd(buf, &r, &g, &b, &id))
        {
            timer1_stop();
            leds[id].r = r;
            leds[id].g = g;
            leds[id].b = b;
            update_rgb();
        }
        else
        {
            uart_printstr("ERROR: parsing failed\r\n");
        }
    }
}