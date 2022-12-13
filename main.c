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