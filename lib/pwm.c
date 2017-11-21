#include "pwm.h"


void PWM_initTimer1(){
 TCCR1A |= (1 << COM1A1);
 TCCR1A |= (1 << COM1B1);
 // set none-inverting mode
 #ifdef PWM_8bit
 TCCR1A |= (1 << WGM10);
 TCCR1B |= (1 << WGM12);
 #endif
 #ifdef PWM_10bit
 TCCR1A |= (1 << WGM11) | (1 << WGM10);
 TCCR1B |= (1 << WGM12);
 #endif
 TCCR1B |= (1 << CS10);
}
void PWM_initTimer2(){
 TCCR2 |= (1 << WGM20) | (1 << WGM21);
 TCCR2 |= (1 << COM21);
 TCCR2 |= (1 << CS20);
}


__inline__ void PWM_setOC1A(pwm_value value){
 OCR1A = value;
}
__inline__ void PWM_setOC1B(pwm_value value){
 OCR1B = value;
}
__inline__ void PWM_setOCR2(uint8_t value){
 OCR2 = value;
}

