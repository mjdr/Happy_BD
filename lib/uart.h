#pragma once

#include "default.h"
#include <avr/io.h>
#define BAUD 9600

void UART_init();
void UART_trasmit(uint8_t);
uint8_t UART_receive();
