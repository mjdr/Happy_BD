#include "writer.h"


void WRITER_writeChar(void (*write_func)(uint8_t), uint8_t c){
 (*write_func)(c);
}

void WRITER_writeString(void (*write_func)(uint8_t), uint8_t* string){
uint8_t c,i = 0;
 while((c = string[i++]) != '\0')
  (*write_func)(c);
}


void WRITER_writeHex32(void (*write_func)(uint8_t), uint32_t c){
 WRITER_writeString(write_func, "0x");
 for(char i = 7;i >= 0;i--){
  uint16_t d = (c & (0b1111 << (4*i))) >> (4*i);
  if(d < 10)
   WRITER_writeChar(write_func, '0' + d);
  else
   WRITER_writeChar(write_func, 'A' + (d - 10));
 }
}

void WRITER_writeHex16(void (*write_func)(uint8_t), uint16_t c){
 WRITER_writeString(write_func, "0x");
 for(char i = 3;i >= 0;i--){
  uint16_t d = (c & (0b1111 << (4*i))) >> (4*i);
  if(d < 10)
   WRITER_writeChar(write_func, '0' + d);
  else
   WRITER_writeChar(write_func, 'A' + (d - 10));
 }
}


void WRITER_writeHex8(void (*write_func)(uint8_t), uint8_t c){
 WRITER_writeString(write_func, "0x");
 for(uint8_t i = 1;i >= 0;i--){
  uint8_t d = (c & (0b1111 << (4*i))) >> (4*i);
  if(d < 10)
   WRITER_writeChar(write_func, '0' + d);
  else
   WRITER_writeChar(write_func, 'A' + (d - 10));
 }
}


void WRITER_writeDec16(void (*write_func)(uint8_t), uint16_t c){
uint8_t tmp[8];
 for(uint8_t i = 0;i < 8;i++){
  char d = c % 10;
  c /= 10; 
  tmp[i] = '0' + d;
 }

 
 char n = 0;
 for(char i = 0;i < 8;i++) {
  if(tmp[7 - i] == '0'){
   if(!n) continue;
  }
  else
   n = 1;
  WRITER_writeChar(write_func, tmp[7 - i]);
 }
 if(!n)
  WRITER_writeChar(write_func, '0');
}
