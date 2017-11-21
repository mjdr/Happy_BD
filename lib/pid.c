/*
 * pid.c
 *
 *  Created on: Nov 20, 2017
 *      Author: root
 */

#include "pid.h"

//Time function on ms
uint32_t (*timeFunction);

void PID_setTimeFunction(uint32_t (*func)()){
	timeFunction = func;
}
void PID_initParams(PIDParams* params){
	params->lastError = 0;
	params->lastTime = (*timeFunction)();
	params->targetValue = 0;
	params->currentValue = 0;
	params->sumError = 0;
	params->Kp = 0;
	params->Ki = 0;
	params->Kd = 0;

}
double PID_calculteOutput(PIDParams* params){
	uint32_t time = (*timeFunction)();
	double dt = (time - params->lastTime)/1000.0;
	double e = params->targetValue - params->currentValue;

	params->sumError += e * dt;

	double p = e;
	double i = params->sumError;
	double d = (e - params->lastError) / dt;

	params->lastError = e;
	params->lastTime = time;


	return
			p * params->Kp +
			i * params->Ki +
			d * params->Kd;


}

