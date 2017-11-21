#pragma once
#include <avr/io.h>


void WRITER_writeChar(void (*write_func)(uint8_t), uint8_t);
void WRITER_writeString(void (*write_func)(uint8_t), uint8_t*);
void WRITER_writeHex32(void (*write_func)(uint8_t), uint32_t);
void WRITER_writeHex16(void (*write_func)(uint8_t), uint16_t);
void WRITER_writeHex8(void (*write_func)(uint8_t), uint8_t);
void WRITER_writeDec16(void (*write_func)(uint8_t), uint16_t);
