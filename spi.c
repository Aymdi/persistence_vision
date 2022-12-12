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

struct RingBuffer buffer;


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
    SPI_MasterTransmit(data1);
    SPI_MasterTransmit(data2);
}


//test pour l'horloge numérique version 1

/* Idée : La pâle met environ 45-50ms à faire un tour donc si on découpe le cercle en 50 sections, chacune de 1ms
   on peut afficher au moins 10 lettres si on considère qu'une Lettre s'affiche sur une largeur de 5 colonnes et 5ms
*/

//#################################     CONFIGURATION    #########################################          



void printLetter(char letter[])
{
    int y;
    // printing the first y row of the letter
    for (y=0; y<5; y++)
    {
        // SPI_MasterTransmit(letter[y]);
        envoie_Led(letter[y], 0b00000000);
        //envoie_Led(0b00000000, 0b00000000);
        _delay_ms(1.5);
    }
    // printing the space between the letters
    //SPI_MasterTransmit(0);
    envoie_Led(0b00000000 , 0b00000000);
    _delay_ms(4);
}

void main(){

    SPI_MasterInit();
    PORTC &= ~_BV(PC1); // /OE == 0
    PORTC &= ~_BV(PC2); // LE == 0

    char a=1;
    char b=0;
    int  i=0;


    DDRB  = 0b00000001;
    PORTB = 0b00000000;
    USART_Init(MYUBRR);
    ringBufferInit(&buffer);

    //unsigned char letter[] ="hey";
    while (1){

        ringBufferWrite(&buffer, USART_Receive());
        if (ringBufferAvailable(&buffer)){
            USART_Transmit(ringBufferRead(&buffer));
        }

        //printLetter(letter);
        //printLetter(s);

        envoie_Led(a,b);
        PORTC |= _BV(PC2); // LE == 1
        PORTC &= ~_BV(PC2); // LE == 0
        _delay_ms(500);
        a = 1 << i;
        i++;
        i = i%8;
    }
}

