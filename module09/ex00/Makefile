TARGET = main

MCU = atmega328p
PORT = /dev/ttyUSB0
F_CPU = 16000000UL
UART_BAUDRATE = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -DUART_BAUDRATE=$(UART_BAUDRATE) \
         -Iinc

SRCS = src/main.c src/i2c.c src/exp.c
OBJS = $(SRCS:src/%.c=obj/%.o)

all: hex flash

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).elf

hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

flash: hex
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(UART_BAUDRATE) \
	-U flash:w:$(TARGET).hex:i

clean:
	rm -rf obj

fclean: clean
	rm -f $(TARGET).elf $(TARGET).hex

re: fclean all

screen: all
	screen $(PORT) $(UART_BAUDRATE)

.PHONY: all hex flash clean fclean re screen