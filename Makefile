BIN=led_test_PD6
OBJS=led_test_PD6.o test.o

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=13000000UL -mmcu=atmega328p
PORT=/dev/ttyACM0

all: 

${BIN}.hex: ${BIN}.elf
    ${OBJCOPY} -O ihex -R .eeprom $< $@

${BIN}.elf: ${OBJS}
    ${CC} -o $@ $^

install: ${BIN}.hex
	avrdude -F -V -c usbasp -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:$<

clean:
    rm -f ${BIN}.elf ${BIN}.hex ${OBJS}