#pragma once

#include <avr/io.h>
#include "writer.h"

#define MAX7219_TEST

#define DDR_SS DDRC
#define PORT_SS PORTC
#define PIN_SS 0


void MAX7219_init(PrintFunc printFunc);
void MAX7219_clearBuffer();
void MAX7219_setPixel(uint8_t, uint8_t);
void MAX7219_setIntensity(uint8_t);
void MAX7219_sendBuffer();

#ifdef MAX7219_TEST
	void MAX7219_test();
#endif


