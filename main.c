#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "effet_Hall.h"
#include "com_blue.h"
#include "spi.h"


void main() {
    SPI_MasterInit();
    char a=1;
    char b=0;
    int i=0;

    DDRD = DDRD | _BV(PD6);
    //DDRD = DDRD | 0b01000000;
    DDRD = DDRD & ~(_BV(PD2));

    while (1){
        if (!(PIND & _BV(PD2))){
            envoie_Led(1,0);
            //PORTC &= ~_BV(PC1); // /OE == 0
            //PORTC &= ~_BV(PC2); // LE == 0
        }
        else{
            Eteint_Led();
        }
    }

    /*
    while (1){
        envoie_Led(0,0);
        PORTC |= _BV(PC2); // LE == 1
        PORTC &= ~_BV(PC2); // LE == 0
        _delay_ms(500);
        a = 1 << i;
        b = 1 << i;
        i++;
        i = i%8;

    }*/


}
/*
ISR()
{
	PORTB ^= (1 << PORTB0);
}*/