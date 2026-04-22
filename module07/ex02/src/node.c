#include "main.h"

uint8_t is_valid_node(t_node *n)
{
    if (n->magic_nb != 0xBEEF)
        return 0;

    if (n->integrity != compute_integrity(n))
        return 0;

    return 1;
}

uint16_t compute_integrity(const t_node *n)
{
    uint16_t sum = 0;

    // id (4 bytes)
    const uint8_t *p = (const uint8_t*)&n->id;
    for (uint8_t i = 0; i < sizeof(n->id); i++)
        sum += p[i];

    // priority (2 bytes)
    p = (const uint8_t*)&n->priority;
    for (uint8_t i = 0; i < sizeof(n->priority); i++)
        sum += p[i];

    // tag (33 bytes)
    for (uint8_t i = 0; i < sizeof(n->tag); i++)
        sum += (uint8_t)n->tag[i];

    return sum;
}

uint8_t save_node(void)
{
    if (slot < debug_fail_slot) // simulate a saving fail
        return 0;

    t_node tmp;

    node.integrity = compute_integrity(&node);

    eeprom_write_node(&node);

    eeprom_read_node(&tmp);

    if (mem_cmp(&node, &tmp, sizeof(t_node)) != 0)
        return 0;

    return 1;
}

void relocate_node(void)
{
    uint8_t start = slot;

    for (uint8_t i = 1; i <= SLOT_COUNT; i++)
    {
        slot = (start + i) % SLOT_COUNT;

        uart_printstr("Relocating config to slot ");
        uart_print_uint32(slot + 1);
        uart_printstr("... ");

        uint8_t old_version = node.version + 1;
        node.version++;

        if (save_node())
        {
            uart_printstr("Success\r\n");
            return;
        }
        uart_printstr("Fail\r\n");
        node.version = old_version;
    }

    uart_printstr("CRITICAL EEPROM FAILURE\r\n");
    slot = SLOT_INVALID;
}