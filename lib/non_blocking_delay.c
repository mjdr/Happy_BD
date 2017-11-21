#include "non_blocking_delay.h"
#include "default.h"


uint32_t (*timeFunction)() = 0;

__inline__ void DELAY_setTimeFunction(uint32_t (*tf)()){
	timeFunction = tf;
}
void DELAY_init(Delay* delay){
	delay->startTime = -1;
	delay->duration = 0;
}
void DELAY_setup(Delay* delay, uint16_t duration){
	delay->startTime = (*timeFunction)();
	delay->duration = duration;
}
boolean DELAY_isOver(Delay* delay){
	if(delay->startTime == -1) return true;

	uint32_t t = (*timeFunction)();

	if((delay->startTime + delay->duration) <= t){
		delay->startTime = -1;
		return true;
	}

	return false;
}
