/*
 * sound.c
 *
 *  Created on: Nov 2, 2017
 *      Author: root
 */

#include "sound.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "non_blocking_delay.h"
#include "uart.h"
#include "writer.h"

enum NOTES {
 C1 =  0, Cs1, D1, Ds1, E1, F1, Fs1, G1, Gs1, A1, As1, B1,
 C2     , Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2, A2, As2, B2,
 C3     , Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3
};

const int8_t music[] = {
		G2,G2,A2,G2,C2,D2,G2,G2,A2,G2,D2,C2,G2,G2,G3,E2,C2,B2,A2,F2,F2,E2,C2,D2,C2
};



void setTone(double);
double getNoteFreq(char);

#define setNote(N) setTone(getNoteFreq(N))

#define SOUND_TIMER_PRESCALER ((1 << CS22) | (1 << CS21))
#define SOUND_TIMER_PRESCALER_VALUE 256
#define SOUND_ON TCCR2B |= SOUND_TIMER_PRESCALER
#define SOUND_OFF TCCR2B &= ~SOUND_TIMER_PRESCALER

#define STATE_PLAY_NOTE 0
#define STATE_PAUSE 1
#define STATE_DONE 2




static Delay delay;
static int8_t state;
static int8_t currentNote;

void SOUND_init(){
	//Timer init
	TCCR2A |= (1 << WGM21);
	TCCR2A |= (1 << COM2A0);


	DDRB |= (1 << PIN3);
	DDRB |= (1 << PIN0);


	state = STATE_PAUSE;
	currentNote = 0;


}
void SOUND_update(){
	if(!DELAY_isOver(&delay)) return ;

	if(state == STATE_PAUSE) {
		setNote(music[currentNote]);
		SOUND_ON;
		state = STATE_PLAY_NOTE;
		DELAY_setup(&delay, 40);
	}
	else if(state == STATE_PLAY_NOTE) {
		SOUND_OFF;
		currentNote++;
		if(currentNote >= sizeof(music)/sizeof(int8_t))
			state = STATE_DONE;
		else
			state = STATE_PAUSE;

		DELAY_setup(&delay, 10);
	}
	else if(state == STATE_DONE){
		DDRB &= ~(1 << PIN3);
		PORTB |= (1 << PIN0);
	}

}


void setTone(double freq){
	double ocr = 16e6f/(2.0 * SOUND_TIMER_PRESCALER_VALUE * freq) - 1;
	if(ocr < 0) ocr = 0;
	else if(ocr > 255) ocr = 255;

	OCR2A = (uint8_t)ocr;
}
double getNoteFreq(char n){
	double nn = n - 24;
	return 440.0 * pow(2,(nn)/12.0);
}
