TARGET = main
TARGET_ELF = $(D_OBJ)$(TARGET).elf

MCU = atmega328p
PORT_1 = /dev/ttyUSB0
PORT_2 = /dev/ttyUSB1
F_CPU = 16000000UL
UART_BAUDRATE = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -DUART_BAUDRATE=$(UART_BAUDRATE) \
         -Iinc

D_SRC = src/
SRCS = main.c timer.c button.c i2c.c uart.c game.c event.c

D_OBJ = .obj/
OBJS = $(addprefix $(D_OBJ), $(SRCS:%.c=%.o))

all: hex flash

$(D_OBJ)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_ELF): $(OBJS)
	$(CC) $(CFLAGS) $^ -o$@

hex: $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $(TARGET).hex

flash: hex
	$(AVRDUDE) -c arduino -p m328p -P $(PORT_1) -b $(UART_BAUDRATE) \
	-U flash:w:$(TARGET).hex:i
	$(AVRDUDE) -c arduino -p m328p -P $(PORT_2) -b $(UART_BAUDRATE) \
	-U flash:w:$(TARGET).hex:i

clean:
	rm -rf $(D_OBJ)
	rm -f $(TARGET).elf $(TARGET).hex

screen:
	TERM=xterm-256color screen $(PORT_1) $(UART_BAUDRATE)

.PHONY: all hex flash clean screen
