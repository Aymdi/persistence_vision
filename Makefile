SRC_DIR=./src
TST_DIR=./test

BIN=main
OBJS=main.o effet_Hall.o com_blue.o buffer.o

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=13000000UL -mmcu=atmega328p


all: $(BIN).hex

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJS)
	$(CC) -mmcu=atmega328p -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install: main.hex
	avrdude -F -V -c usbasp -p ATMEGA328P -P -b 115200 -U flash:w:main.hex

clean:
	rm -f $(BIN).elf *.o *.hex ${OBJS}