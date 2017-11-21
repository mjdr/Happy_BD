#pragma once
#include <avr/io.h>


void ADC_init();
void ADC_setChannel(char);
uint16_t ADC_read();
