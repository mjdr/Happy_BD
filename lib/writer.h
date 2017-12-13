#pragma once
#include <avr/io.h>

typedef void(*PrintFunc)(uint8_t);


void WRITER_writeChar(PrintFunc, uint8_t);
void WRITER_writeString(PrintFunc, uint8_t*);
void WRITER_writeLine(PrintFunc, uint8_t*);
void WRITER_writeHex32(PrintFunc, uint32_t);
void WRITER_writeHex16(PrintFunc, uint16_t);
void WRITER_writeHex8(PrintFunc, uint8_t);
void WRITER_writeDec16(PrintFunc, uint16_t);
