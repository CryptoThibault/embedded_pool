#include "main.h"

void status(void)
{
    if (slot == SLOT_INVALID)
    {
        uart_printstr("ERROR: Node unconfigured\r\n");
        return;
    }
    if (!is_valid_node(&node))
    {
        uart_printstr("CRITICAL: Data corruption detected!\r\n");
        return;
    }
    uart_printstr("Node ID: ");
    uart_print_uint32(node.id);
    uart_printstr("\r\nPriority: ");
    uart_print_int16(node.priority);
    uart_printstr("\r\nSlot: ");
    uart_print_uint32(slot + 1);
    uart_printstr("\r\nTag: \"");
    uart_printstr((char*)node.tag);
    uart_printstr("\"\r\n");
}

void set_id(uint32_t id)
{
    node.id = id;
    if (!save_node()) relocate_node();
}

void set_prio(int16_t prio)
{
    node.priority = prio;
    if (!save_node()) relocate_node();
}

void set_tag(const char* tag)
{
    str_cpy(node.tag, tag);
    if (!save_node()) relocate_node();
}

void factory_reset(void)
{
    uart_printstr("===FACTORY RESET===\r\n");
    uint16_t invalid = 0x0000;

    for (uint8_t i = 0; i < SLOT_COUNT; i++)
    {
        eeprom_write_word(
            (uint16_t*)(i * sizeof(t_node)),
            invalid
        );
    }

    node = (t_node)
    {
        .magic_nb = 0xBEEF,
        .id = 0,
        .priority = 0,
        .tag = "Unconfigured",
        .version = 1,
        .integrity = 0
    };

    slot = 0;
    debug_fail_slot = 0;

    save_node();
}