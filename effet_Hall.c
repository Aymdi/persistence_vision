#include "effet_Hall.h"


void hall() {
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

}