#pragma once
#include "default.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


#define MOSI_DDR DDRC
#define MOSI_PORT PORTC
#define MOSI_PIN 1

#define SCK_DDR DDRC
#define SCK_PORT PORTC
#define SCK_PIN 2


void SOFTSPI_init();
void SOFTSPI_send(uint8_t);
