#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#include "effet_Hall.h"
#include "com_blue.h"
#include "buffer.h"
#include "spi.h"

int compteur_secondes=0;
int extraTime=0;

void init_interrupt(){

    // Make it to input
    DDRD &= ~(1<<DDD0); 
    PORTD |= (1<<PORTD0);
    
    // Enable interruption of detector on rising edge 
    EICRA |= (1<<ISC01)|(1<<ISC00);

    // Activate INT0
    EIMSK |= (1<<INT0);
    
    // Set global interrupt enable
    sei();//réactive les interruptions configurées 

    //SREG |= (1<<I); //Met le bit à 1 du global interrupt du status register, permet d'activer les interruptions

}


ISR(TIMER0_COMPA_vect){// c'est une interruption qui s'active quand 
//le compteur du timer0 arrive à sa valeur max predefinie(autoreload)
    TCNT0 = 0; // s'incrèmente à une une frequence 13MHz/prescaler 
    envoie_Led(0b11000000,0);
    compteur_secondes++;

}

void init_seconds(void){
  TIMSK0 |=(1<<OCIE0A);
  TCCR0B |= (1<<WGM02); 
  TCCR0B |= (1<<CS01)|(1<<CS00); //start at 64 prescalar
  OCR0A = 250; // autoreload value pour la détection d'une seconde 
}

ISR(TIMER1_COMPA_vect){// c'est une interruption qui s'active quand 
//le compteur du timer1 arrive à sa valeur max predefinie(autoreload)
    TCNT1 = 0;
    extraTime++;
}

void init_compteur_timer(void){
  TIMSK1 |=(1<<OCIE1A);
  TCCR1B |= (1<<WGM12); 
  TCCR1A |= (1<<WGM11)|(1<<WGM10);
  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);

  OCR1AH=0;
  OCR1AL=250; // autoreload value
}


int main(void){

    SPI_MasterInit();
    init_seconds();
    //init_counter_time();
    USART_init();
    
    PORTC &= ~_BV(PC1); // /OE == 0
    PORTC &= ~_BV(PC2); // LE == 0

    unsigned char test;
    ringBufferInit(buffer);
    int x = 0;
    while(1){
        if((!(PIND & _BV(PD2)))) //logique inverse : signal HALL =1 => pas d'aimant, si Hall =0 alors présence aimant)
        {   
            //x++; //pour la vitesse de rotation
            envoie_Led(0b11111111,0b11111111);
            PORTC |= _BV(PC2); // LE == 1
            PORTC &= ~_BV(PC2); // LE == 0
            _delay_ms(50);
            envoie_Led(0b00000000,0b00000000);
            PORTC |= _BV(PC2); // LE == 1
            PORTC &= ~_BV(PC2); // LE == 0
            //USART_Transmit(x);
    }
    }

    return 0;
}

/*#include "spi.h"
#include "effet_Hall.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>

void printLetter(char letter[])
{
    int y;
    // printing the first y row of the letter
    for (y=0; y<5; y++)
    {
        // SPI_MasterTransmit(letter[y]);
        //Allume_Led(letter[y], 0b00000000);
        envoie_Led(0b00000000, letter[y]);
        //Allume_Led(0b00000000, 0b00000000);
        _delay_ms(0.5);
    }
    // printing the space between the letters
    //SPI_MasterTransmit(0);
    envoie_Led(0b00000000 , 0b00000000);
    _delay_ms(1);
} 



int main(){
    // Init
    // USART_init();

    SPI_MasterInit();
    // Pin is output (low impedance) - LED bleue
    DDRD |= _BV(PD6);
    // Pin is input (bit 2 == 0) - entrée pin effet Hall
    DDRD &= ~_BV(PD2);        

    char NUMBER9_INV[]= {0b11110001, 0b10010001, 0b10010001, 0b10010001, 0b11111111};
    char NUMBER9[]= {0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b11110001};
    char NUMBER8[]= {0b01101110, 0b10010001, 0b10010001, 0b10010001, 0b01101110};

    char NUMBER7_INV[]= {0b10000000, 0b10001000, 0b10001000, 0b10011111, 0b11101000};
    char NUMBER7[]= {0b11101000, 0b10011111, 0b10001000, 0b10001000, 0b10000000};
    char NUMBER6_INV[]= {0b11111111, 0b10001001, 0b10001001, 0b10001001, 0b10001111};
    char NUMBER6[]= {0b10001111, 0b10001001, 0b10001001, 0b10001001, 0b11111111};
    char NUMBER5_INV[]= {0b11111001, 0b10001001, 0b10001001, 0b10001001, 0b10001111};
    char NUMBER5[]= {0b10001111, 0b10001001, 0b10001001, 0b10001001, 0b11111001};

    char NUMBER2_INV[]= {0b10000011, 0b10000101, 0b10001001, 0b10010001, 0b01100001};
    char NUMBER2[]= {0b01100001, 0b10010001, 0b10001001, 0b10000101, 0b10000011};
    char NUMBER1_INV[]= {0b00100000, 0b01000000, 0b11111111, 0b00000000, 0b00000000};
    char NUMBER1[]= {0b00000000, 0b00000000, 0b11111111, 0b01000000, 0b00100000};
    char NUMBER0[]= {0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b11111111};

    char _[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000};
    char A[] = {0b11111111, 0b10010000, 0b10010000, 0b10010000, 0b11111111};
    char B[] = {0b01101110, 0b10010001, 0b10010001, 0b10010001, 0b11111111};
    char C[] = {0b10000001, 0b10000001, 0b10000001, 0b01000010, 0b00111100};

    char E_INV[] = {0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b10010001};
    char E[] = {0b10010001, 0b10010001, 0b10010001, 0b10010001, 0b11111111};
    char H_INV[] = {0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b11111111};
    char H[] = {0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b11111111};
    char L_INV[] = {0b11111111, 0b00000001, 0b00000001, 0b00000001, 0b00000001};
    char L[] = {0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b11111111};
    char O[] = {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b01111110};

    // Body
    while(1){

/*      PORTD |= _BV(PD6); // LED ON
        _delay_ms(2000);

        char data1 =  0b00000000;
        char data2 =  0b11111111; 
        Allume_Led(data1, data2);
        _delay_ms(4000);
        Eteint_Led();
        _delay_ms(2000);
        PORTD &= ~_BV(PD6); // Blue LED OFF
        _delay_ms(2000);  */

        // Pin is input (bit 2 == 0) - entrée pin effet Hall
        /*DDRD &= ~_BV(PD2);     

        if (!(PIND & 0x04))
        {
            printLetter (A);
            printLetter (L);
            printLetter (O);
            printLetter (H);
        }*/

/*         char* message[]= {NUMBER9,NUMBER8,_,A,B,C '/0'}; 
        printMessage(message);  */
    //}
//}
