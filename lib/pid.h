/*
 * pid.h
 *
 *  Created on: Nov 20, 2017
 *      Author: root
 */

#pragma once

typedef struct {
	uint32_t lastTime;
	double lastError;
	double sumError;
	double Kp,Ki,Kd;
	double targetValue;
	double currentValue;
} PIDParams;

void PID_setTimeFunction(uint32_t (*)());
void PID_initParams(PIDParams*);
double PID_calculteOutput(PIDParams*);



