#include "main.h"

t_node node;
uint8_t slot = SLOT_INVALID;
uint8_t debug_fail_slot = 0;

int main()
{
    uart_init();

    load_from_eeprom();

    while (1)
    {
        char cmd[BUFFER_SIZE];
        uint8_t i = 0;
        uart_printstr("> ");

        while (!uart_line_process(cmd, &i));

        char *p = cmd;
        char *token = next_token(&p);
        if (!token)
            continue;

        if (str_equal(token, "STATUS"))
        {
            status();
        }
        else if (str_equal(token, "SET_ID"))
        {
            char *arg = next_token(&p);
            uint32_t id;

            if (arg && parse_u32(arg, &id))
                set_id(id);
            else
                uart_printstr("ERROR: missing ID\r\n");
        }
        else if (str_equal(token, "SET_PRIO"))
        {
            char *arg = next_token(&p);
            int16_t prio;

            if (arg && parse_i16(arg, &prio))
                set_prio(prio);
            else
                uart_printstr("ERROR: missing PRIO\r\n");
        }
        else if (str_equal(token, "SET_TAG"))
        {
            char *arg = next_token(&p);

            if (arg)
            {
                char tag[33];
                if (parse_tag(arg, tag)) set_tag(tag);
                else uart_printstr("ERROR: invalid tag format\r\n");
            }
            else
            {
                uart_printstr("ERROR: missing TAG\r\n");
            }
        }
        else if (str_equal(token, "FACTORY_RESET"))
        {
            factory_reset();
        }
        else if (str_equal(token, "DEBUG"))
        {
            char *arg = next_token(&p);
            uint32_t val;

            if (!arg || !parse_u32(arg, &val) || val > SLOT_COUNT)
                uart_printstr("ERROR: invalid debug slot\r\n");
            else
                debug_fail_slot = (uint8_t)val;
        }
        else
        {
            uart_printstr("ERROR: Invalid command\r\n");
        }
    }
}