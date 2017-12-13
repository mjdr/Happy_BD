#include "default.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "non_blocking_delay.h"
#include "time.h"
#include "writer.h"
#include "eeprom_buffer.h"
#include "uart.h"


#include "sound.h"
#include "led_matrix.h"

void main(){

	TIME_init();
	UART_init();

	DELAY_setTimeFunction(&TIME_get);
	SOUND_init();
	MATRIX_init();


	while(1){
		SOUND_update();
		MATRIX_update();
	}

}







