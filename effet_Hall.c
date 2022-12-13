/*#include <avr/io.h>
#include <util/delay.h>

//faire clignoter la led rouge par effet hall
void effet_Hall() {
    // Enables and turn the PB5 pin ON (led)
    DDRD = DDRD | _BV(PD6);
    //DDRD = DDRD | 0b01000000;
    DDRD = DDRD & ~(_BV(PD2));
    while(1){
       // PORTD = PORTD | _BV(PD6); led PD6 allumée
        if (!(PIND & _BV(PD2))){ //logique inverse : signal HALL =1 => pas d'aimant, si Hall =0 alors présence aimant
            PORTD = PORTD | _BV(PD6);//led PD6 allumée
        }
        else{
            PORTD = PORTD & ~(_BV(PD6)); //led PD6 éteinte
            }
    }

}*/


//version avec interruption 
#include "com_blue.h"
#include "effet_Hall.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


void init_hall()
{
    // Make it to input
    DDRD &= ~(1<<DDD0); 
    PORTD |= (1<<PORTD0);
    // Enable interruption of detector on rising edge 
    EICRA |= (1<<ISC01)|(1<<ISC00);
    // Activate INT0
    EIMSK |= (1<<INT0);
    // Set global interrupt enable
    sei();  
}

ISR(INT0_vect){//lorsqu'on passe devant l'aimant, on allume la led 1

    detection_Hall++;
}