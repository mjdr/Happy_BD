#include "adc.h"


void ADC_init(){
 ADCSRA |= (1 << ADEN) | (1<<ADPS2) | (1<<ADPS0);
 ADMUX=(1<<REFS0);
}

__inline__ void ADC_setChannel(char channel){
 ADMUX &= ~0b111;
 ADMUX |= channel & 0b111;
}

__inline__ uint16_t ADC_read(){
 ADCSRA |= (1 << ADSC);
 while(!(ADCSRA & (1 << ADIF)));
 ADCSRA |= (1 << ADIF);
 return ADC;
}
