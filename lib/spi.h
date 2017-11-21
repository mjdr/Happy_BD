#pragma once

#include <avr/io.h>

#define DDR_SPI DDRB
#define DD_MOSI 3
#define DD_SCK 5

void SPI_init();
uint8_t SPI_transmit(uint8_t);
void SPI_send(uint8_t);
uint8_t SPI_receive();


