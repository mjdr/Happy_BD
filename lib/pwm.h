#pragma once
#include <avr/io.h>

#define PWM_8bit

#ifdef PWM_8bit
 //F_CPU 1MHz ------ F_PWM 3.83kHz
 typedef char pwm_value;
#endif
#ifdef PWM_10bit
 //F_CPU 1MHz ------ F_PWM 960Hz
 typedef int pwm_value;
#endif


void PWM_initTimer1();
void PWM_setOC1A(pwm_value);
void PWM_setOC1B(pwm_value);


//Timer2 
//F_CPU 1MHz ------ F_PWM 4.8kHz
void PWM_initTimer2();
void PWM_setOCR2(uint8_t);

