TARGET = main

MCU = atmega328p
F_CPU = 16000000UL
UART_BAUDRATE = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -DUART_BAUDRATE=$(UART_BAUDRATE)

all: hex flash

hex: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).bin $(TARGET).c
	$(OBJCOPY) -O binary $(TARGET).bin $(TARGET).hex

flash: $(TARGET).hex
	$(AVRDUDE) -c arduino -p m328p -P /dev/ttyUSB0 -b $(UART_BAUDRATE) -U flash:w:$(TARGET).hex

clean:
	rm $(TARGET).bin
	rm $(TARGET).hex

.PHONY: all hex flash clean