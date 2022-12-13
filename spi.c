#define F_CPU 13000000UL // Clock Speed
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include "buffer.h"
#include "com_blue.h"

// SDI == MOSI == PB3
// /OE == PC1
// SCK == PB5
// LE == PC2



void Eteint_Led(){
    PORTC |= _BV(PC1); // /OE == 1
    PORTC &= ~_BV(PC2); // LE == 0
}


void SPI_MasterInit(void)
{
    /* met MOSI et SCK en output, les autres en input input */
    DDRB = (1<<DDB3)|(1<<DDB5)|(1<<DDB2);

    /* Enable SPI, Master, set clock rate fck/16 */

    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    DDRC |= _BV(PC1); // /OE
    DDRC |= _BV(PC2); // LE

    Eteint_Led();
}

void SPI_MasterTransmit(char cData)
{
    /* commence la transmission */
    SPDR = cData;

    /* attend que la transmission soit comlplète */
    while(!(SPSR & (1<<SPIF)));
}


void envoie_Led(uint8_t data1, uint8_t data2){

    PORTC |= (1<<PORTC1);
    SPI_MasterTransmit(data1);
    SPI_MasterTransmit(data2);
    PORTC |= (1<<PORTC2);
    PORTC &= ~(1<<PORTC2);
    PORTC &= ~(1<<PORTC1);

}

