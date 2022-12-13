#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_8bit.h"

/*
int main(void)
{
	cli(); //pour desactiver toutes les interruptions globalement
	DDRB = 0x01;
	
	TCCR0A = (1 << WGM01); //Set CTC Bit
	OCR0A = 195;
	TIMSK0 = (1 << OCIE0A);
	
	sei(); //réactive les interruptions configurées 
	
	TCCR0B = (1 << CS02) | (1 << CS00); //start at 1024 prescalar
	
    while(1)
    {
        //code d'application : boucle principale
    }
}*/

ISR(TIMER0_COMPA_vect) // c'est une interruption qui s'active quand 
//le compteur du timer0 arrive à sa valeur max predefinie(autoreload)
{
	extraTime++;
	
}