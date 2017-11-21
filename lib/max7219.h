/*
 * max7219.h
 *
 *  Created on: Nov 16, 2017
 *      Author: root
 */

#pragma once

#include <avr/io.h>

#define MAX7219_TEST

#define PORT_SS PORTB
#define PIN_SS PIN2


#define SS_UP PORT_SS |= (1<<PIN_SS)
#define SS_DOWN PORT_SS &= ~(1<<PIN_SS)

void MAX7219_init(void(*)(uint8_t));
void MAX7219_clearBuffer();
void MAX7219_setPixel(uint8_t, uint8_t);
void MAX7219_setIntensity(uint8_t);
void MAX7219_sendBuffer();

#ifdef MAX7219_TEST
	void MAX7219_test();
#endif


