#include "default.h"
#include "led_matrix.h"
#include "non_blocking_delay.h"
#include <avr/interrupt.h>
#include "max7219.h"
#include "soft_spi.h"
#include "uart.h"
#include "writer.h"
#include <math.h>


static Delay delay;
static uint16_t nFrame = 0;
volatile char updatedRow = 0;


void MATRIX_render();


void MATRIX_init() {

	SOFTSPI_init();
	MAX7219_init(&SOFTSPI_send);

	MAX7219_clearBuffer();
	MAX7219_sendBuffer();


}

void MATRIX_update() {
	if(!DELAY_isOver(&delay)) return;

	MAX7219_clearBuffer();
	MATRIX_render();
	MAX7219_sendBuffer();

	DELAY_setup(&delay,10);

}


void MATRIX_render(){


	//Actually rendering process
	for(int c = 0;c < 8;c++){
		int y = 3 + (int)(ceil(3 * sin((nFrame+c*0.75)/2.1)));
		if(y >= 0 && y <= 8)
			MAX7219_setPixel(c, (int)y);
	}

	nFrame++;
}



