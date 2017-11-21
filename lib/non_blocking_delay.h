#pragma once

#include <stdint.h>

typedef struct {
 int32_t startTime;
 int16_t duration;
} Delay;



void DELAY_setTimeFunction(uint32_t(*)());
void DELAY_init(Delay*);
void DELAY_setup(Delay*, uint16_t);
char DELAY_isOver(Delay*);
