#ifndef TIMER
#define TIMER

#include "avr/io.h"

extern int extraTime;

void timer_init(void);

uint8_t get_sec(void);

uint8_t get_min(void);

uint8_t get_hour(void);

void set_sec(uint8_t sec);

void set_min(uint8_t min);

void set_hour(uint8_t hour);


#endif