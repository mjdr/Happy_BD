#pragma once

#include "default.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include "pwm.h"


void ROTARY_init();
long ROTARY_getStep();
void ROTARY_moveTo(uint32_t);

