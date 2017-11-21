#include "rotary_encoder.h"

#define R_PIN PIND
#define STATE() (R_PIN & 0b11)
#define STATE2() ((R_PIN & 0b1100) >> 2)

#define LED_ON PORTB |= (1 << 1)
#define LED_OFF PORTB &= ~(1 << 1)

#define MOTOR_ON PORTB |= 0b1
#define MOTOR_OFF PORTB &= ~(1 << 1)


const uint8_t table[4][4] = {
	{ 0, 1,-1, 0},
	{-1, 0, 0, 1},
	{ 1, 0, 0,-1},
	{-1, 0, 1, 0}
};

volatile char state;
volatile long step;
volatile long nextStep;
volatile char done;

void updateState() {
	uint8_t newState = STATE();
	if(state == newState) return;

	uint8_t v = table[state][newState];
	step += v;
	state = newState;

	PORTD &= ~(0b11111100);
	PORTD |= (step >> 10) << 2;
}


void updateMove(){
	if(!done && step >= nextStep){
		PORTB &= ~0b1;
		done = true;
		LED_OFF;
	}
}


ISR(TIMER2_OVF_vect){
 updateState();
 updateMove();
}



void ROTARY_init(){
	TIMSK |= (1 << TOIE2);
	sei();

	state = STATE();
	step = 0;
	done = true;
	LED_OFF;
	DDRB |= 0b11;
	DDRD |= 0b11111100;
}

long ROTARY_getStep(){
	return step;
}

void ROTARY_moveTo(uint32_t pos) {
	nextStep = pos;
	MOTOR_ON;
	done = false;
	LED_ON;
	while(!done);
}

