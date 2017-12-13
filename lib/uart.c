#include "uart.h"


#define MYUBRR (F_CPU/16/BAUD-1)



void UART_init(){
 UBRR0H = (uint8_t)(MYUBRR>>8);
 UBRR0L = (uint8_t) MYUBRR;
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void UART_trasmit(uint8_t data){
 wait_for_one(UCSR0A, UDRE0);
 UDR0 = data;
 wait_for_one(UCSR0A, UDRE0);
}

uint8_t UART_receive(){
 wait_for_one(UCSR0A, RXC0);
 return UDR0;
}




