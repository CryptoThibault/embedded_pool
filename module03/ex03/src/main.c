#include "main.h"

int main()
{
    uint8_t filter = 0;

    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD3);

    uart_init();

    while (1)
    {
        uint8_t i = 0;
        char str[6];

        uart_printstr("Enter a HEX RGB color: \r\n    #");
        while (!uart_line_process(str, &i));

        if (is_hex_string(str))
        {
            uart_printstr("The color is displayed on the LED!\r\n\n");

            uint8_t rgb[3];
            hex_to_rgb(str, rgb);
            if (filter) rgb_filter(rgb);

            if (rgb[0] || rgb[1] || rgb[2])
                init_rgb();
            else
                disable_rgb();

            set_rgb(rgb[0], rgb[1], rgb[2]);
        }
        else
        {
            uart_printstr("Invalid color format, please try again\r\n\n");
        }
    }
}