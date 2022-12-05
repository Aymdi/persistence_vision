avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o com_blue.o com_blue.c
avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o buffer.o buffer.c

avr-gcc -mmcu=atmega328p com_blue.o buffer.o -o com_blue

avr-objcopy -O ihex -R .eeprom com_blue com_blue.hex

avrdude -F -V -c usbasp -p ATMEGA328P -P -b 115200 -U flash:w:com_blue.hex
