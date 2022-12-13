avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o spi.o spi.c
avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o buffer.o buffer.c
avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o com_blue.o com_blue.c
avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o effet_Hall.o effet_Hall.c
avr-gcc -Os -DF_CPU=13000000UL -mmcu=atmega328p -c -o main.o main.c


avr-gcc -mmcu=atmega328p spi.o buffer.o com_blue.o effet_Hall.o main.o -o main

avr-objcopy -O ihex -R .eeprom main main.hex

avrdude -F -V -c usbasp -p ATMEGA328P -P -b 115200 -U flash:w:main.hex
