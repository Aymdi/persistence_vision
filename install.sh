avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o effet_Hall.o effet_Hall.c

avr-gcc -mmcu=atmega328p effet_Hall.o -o effet_Hall

avr-objcopy -O ihex -R .eeprom effet_Hall effet_Hall.hex

avrdude -F -V -c usbasp -p ATMEGA328P -P -b 115200 -U flash:w:effet_Hall.hex
