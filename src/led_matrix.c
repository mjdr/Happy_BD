#include "default.h"
#include "led_matrix.h"
#include "non_blocking_delay.h"
#include <avr/interrupt.h>
#include "max7219.h"



char buffer[8] = {0};
Delay delay;
uint16_t nFrame = 0;
volatile char updatedRow = 0;


void MATRIX_render();

void spiFunc(uint8_t data){}


void MATRIX_init() {
	MAX7219_init(spiFunc);
}

void MATRIX_update() {
	if(!DELAY_isOver(&delay)) return;

	MATRIX_render();
	MAX7219_sendBuffer();

	DELAY_setup(&delay,100);

}


void MATRIX_render(){

	//Actually rendering process


	nFrame++;
}



