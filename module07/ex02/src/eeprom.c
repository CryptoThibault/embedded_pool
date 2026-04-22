#include "main.h"

void eeprom_read_node(t_node *out)
{
    eeprom_read_block(out, (void*)(slot * sizeof(t_node)), sizeof(t_node));
}

void eeprom_write_node(const t_node *node)
{
    uint16_t addr = slot * sizeof(t_node);
    const uint8_t *data = (const uint8_t*)node;

    for (uint16_t i = 0; i < sizeof(t_node); i++)
    {
        uint8_t current = eeprom_read_byte((uint8_t*)(addr + i));

        if (current != data[i])
            eeprom_write_byte((uint8_t*)(addr + i), data[i]);
    }
}

void load_from_eeprom(void)
{
    t_node tmp;
    uint8_t found = 0;
    uint8_t best_slot = 0;
    uint8_t best_version = 0;

    for (uint8_t i = 0; i < SLOT_COUNT; i++)
    {
        eeprom_read_block(&tmp, (void*)(i * sizeof(t_node)), sizeof(t_node));

        if (is_valid_node(&tmp))
        {
            if (!found || tmp.version > best_version)
            {
                node = tmp;
                best_version = tmp.version;
                best_slot = i;
                found = 1;
            }
        }
    }

    if (found)
    {
        slot = best_slot;
        return;
    }

    slot = 0;
    node = (t_node)
    {
        .magic_nb = 0xBEEF,
        .id = 0,
        .priority = 0,
        .tag = "Unconfigured",
        .version = 1,
        .integrity = 0
    };

    save_node();
}