#include <avr/io.h>
#include <util/delay.h>

int main() {
    // Enables and turn the PB5 pin ON (led)
    DDRD = DDRD | _BV(PD6);
    //DDRD = DDRD | 0b01000000;

    while(1){

        PORTD = PORTD | _BV(PD6);
        _delay_ms(2000);
        PORTD = PORTD & ~ (_BV(PD6));
        _delay_ms(2000);
        
    }

}