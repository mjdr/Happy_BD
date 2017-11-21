#include "spi.h"



void SPI_init(){
 DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
 SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t SPI_transmit(uint8_t data) {
 SPDR = data;
 while(!(SPSR & (1<<SPIF)));
 return SPDR;
}

void SPI_send(uint8_t data) {
 SPI_transmit(data);
}

uint8_t SPI_receive() {
 return SPI_transmit(0x00);
}


