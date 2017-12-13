#include "writer.h"


void WRITER_writeChar(PrintFunc printFunc, uint8_t c){
 (*printFunc)(c);
}

void WRITER_writeString(PrintFunc printFunc, uint8_t* string){
uint8_t c,i = 0;
 while((c = string[i++]) != '\0')
  (*printFunc)(c);
}

void WRITER_writeHexN(PrintFunc printFunc, uint32_t c , int n){
	WRITER_writeString(printFunc, "0x");
		for(char i = n - 1;i >= 0;i--){
			uint16_t d = (c & (0xF << (4*i))) >> (4*i);
			if(d < 10)
				WRITER_writeChar(printFunc, '0' + d);
			else
				WRITER_writeChar(printFunc, 'A' + (d - 10));
		}
}

void WRITER_writeHex32(PrintFunc printFunc, uint32_t data){
	WRITER_writeHexN(printFunc,data,8);
}

void WRITER_writeHex16(PrintFunc printFunc, uint16_t data){
	WRITER_writeHexN(printFunc,data,4);
}


void WRITER_writeHex8(PrintFunc printFunc, uint8_t data){
	WRITER_writeHexN(printFunc,data,2);
}




void WRITER_writeDec16(PrintFunc printFunc, uint16_t c){
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
	  WRITER_writeChar(printFunc, tmp[7 - i]);
	 }
	 if(!n)
	  WRITER_writeChar(printFunc, '0');
}



void WRITER_writeLine(PrintFunc printFunc, uint8_t* string){
	WRITER_writeString(printFunc, string);
	WRITER_writeString(printFunc, "\n\r");
}

