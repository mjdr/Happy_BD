/*
 * time.c
 *
 *  Created on: Nov 2, 2017
 *      Author: root
 */

#include "time.h"
#include <avr/interrupt.h>


//1 time unit is 0.1 sec

volatile uint32_t time;

ISR(TIMER0_OVF_vect){
	TCNT0 = 100;
	time++;
}



__inline__ void TIME_init(){
	TCCR0B |= (1 << CS02) | (1 << CS00); //prescaler
	TIMSK0 |= (1 << TOIE0);
	time = 0;
	sei();
}

__inline__ uint32_t TIME_get(){
	return time;
}

