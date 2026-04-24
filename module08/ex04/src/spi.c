#include "main.h"

void spi_init(void)
{
    DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);  // MOSI, SCK, SS as output
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // enable SPI, master, fosc/16
}

uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;                   // start transmission
    while (!(SPSR & (1 << SPIF))); // wait transfer complete
    return SPDR;                   // return received byte
}

void spi_start(void)
{
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);
}

void spi_stop(void)
{
    spi_transfer(0xFF);
    spi_transfer(0xFF);
    spi_transfer(0xFF);
    spi_transfer(0xFF);
}

void spi_set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
{
    spi_transfer(br);
    spi_transfer(b);
    spi_transfer(g);
    spi_transfer(r);
}