#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include "com_blue"


// SDI == MOSI == PB3
// /OE == PC1
// SCK == PB5
// LE == PC2

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

void Eteint_Led(){
    PORTC |= _BV(PC1); // /OE == 1
    PORTC &= ~_BV(PC2); // LE == 0
}


void main(){
    SPI_MasterInit();
    PORTC &= ~_BV(PC1); // /OE == 0
    PORTC |= _BV(PC2); // LE == 1
    SPI_MasterTransmit(0b00000000);
    delay_ms(10);
    SPI_MasterTransmit(0b00000001);
}