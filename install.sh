avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o communication_bluetooth.o communication_bluetooth.c

avr-gcc -mmcu=atmega328p communication_bluetooth.o -o communication_bluetooth

avr-objcopy -O ihex -R .eeprom communication_bluetooth communication_bluetooth.hex

avrdude -F -V -c usbasp -p ATMEGA328P -P -b 115200 -U flash:w:communication_bluetooth.hex
