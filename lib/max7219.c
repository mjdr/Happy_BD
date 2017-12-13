#include "max7219.h"
#include "uart.h"
#include "writer.h"
#include "soft_spi.h"


//#define DEBUG

#define SS_UP PORT_SS |= (1<<PIN_SS)
#define SS_DOWN PORT_SS &= ~(1<<PIN_SS)

//Registers
#define MAX7219_REG_NOOP          0x00
#define MAX7219_REG_DIGIT0        0x01
#define MAX7219_REG_DIGIT1        0x02
#define MAX7219_REG_DIGIT2        0x03
#define MAX7219_REG_DIGIT3        0x04
#define MAX7219_REG_DIGIT4        0x05
#define MAX7219_REG_DIGIT5        0x06
#define MAX7219_REG_DIGIT6        0x07
#define MAX7219_REG_DIGIT7        0x08
#define MAX7219_REG_DECODE_MODE   0x09
#define MAX7219_REG_INTENSITY     0x0A
#define MAX7219_REG_SCAN_LIMIT    0x0B
#define MAX7219_REG_SHUTDOWN      0x0C
#define MAX7219_REG_DISPLAY_TEST  0x0F

//Shutdown Register Format (Address (Hex) = 0xXC)
#define MAX7219_VAL_SHUTDOWN 0x0
#define MAX7219_VAL_NORMAL   0x1

//Display-Test Register Format(Address (Hex) = 0xXF)
#define MAX7219_VAL_TEST_NORMAL   0x0
#define MAX7219_VAL_TEST_TEST     0x1

//Decode-Mode Register Examples (Address (Hex) = 0xX9)
#define MAX7219_VAL_NO_DECODE 0x00
#define MAX7219_VAL_B_FOR_0   0x01
#define MAX7219_VAL_B_FOR_3_0 0x0F
#define MAX7219_VAL_B_FOR_7_0 0xFF

//Intensity Register Format (Address (Hex) = 0xXA)
#define MAX7219_INTENSITY_MIN_VALUE 0
#define MAX7219_INTENSITY_MAX_VALUE 15

//Scan-Limit Register Format (Address (Hex) = 0xXB)
#define MAX7219_VAL_DISPLAY_0   0
#define MAX7219_VAL_DISPLAY_0_1 1
#define MAX7219_VAL_DISPLAY_0_2 2
#define MAX7219_VAL_DISPLAY_0_3 3
#define MAX7219_VAL_DISPLAY_0_4 4
#define MAX7219_VAL_DISPLAY_0_5 5
#define MAX7219_VAL_DISPLAY_0_6 6
#define MAX7219_VAL_DISPLAY_0_7 7





void MAX7219_writeData(uint8_t, uint8_t);
void MAX7219_setShutdownMode(uint8_t);
void MAX7219_setDecodeMode(uint8_t);


PrintFunc spiFunction;
uint8_t MAX7219_buffer[8];


void MAX7219_init(PrintFunc func){
	spiFunction = func;

	DDR_SS |= (1 << PIN_SS);

	//MAX7219_test();

	MAX7219_setShutdownMode(MAX7219_VAL_NORMAL);
	MAX7219_setDecodeMode(MAX7219_VAL_NO_DECODE);
	MAX7219_setIntensity(0);
	MAX7219_writeData(MAX7219_REG_SCAN_LIMIT, 7);
	MAX7219_writeData(MAX7219_REG_DISPLAY_TEST, MAX7219_VAL_TEST_NORMAL);
	MAX7219_clearBuffer();
	MAX7219_sendBuffer();


}


void MAX7219_clearBuffer(){
	//&(uint64_t*)(*MAX7219_buffer) = 0;

	for(uint8_t i = 0;i < 8;i++)
		MAX7219_buffer[i] = 0;

}
__inline__ void MAX7219_setPixel(uint8_t x, uint8_t y){

	x = 7 - x;

	MAX7219_buffer[y] |= (1 << x);
}
__inline__ void MAX7219_setIntensity(uint8_t intensity) {
	MAX7219_writeData(MAX7219_REG_INTENSITY, intensity);
}
__inline__ void MAX7219_setShutdownMode(uint8_t mode){
	MAX7219_writeData(MAX7219_REG_SHUTDOWN, mode);
}
__inline__ void MAX7219_setDecodeMode(uint8_t mode){
	MAX7219_writeData(MAX7219_REG_DECODE_MODE, mode);
}
void MAX7219_sendBuffer(){
	for(uint8_t i = 8;i > 0;i--)
		MAX7219_writeData(i, MAX7219_buffer[i -1]);
}



void MAX7219_writeData(uint8_t reg, uint8_t value){
	SS_DOWN;

	#ifdef DEBUG
		WRITER_writeString(UART_trasmit, "MAX7219: ");
		WRITER_writeHex8(UART_trasmit, reg);
		WRITER_writeString(UART_trasmit, " ");
		WRITER_writeHex8(UART_trasmit, value);
		WRITER_writeString(UART_trasmit, "\n\r");
	#endif

	(*spiFunction)(reg);
	(*spiFunction)(value);
	SS_UP;
}



#ifdef MAX7219_TEST
	__inline__ void MAX7219_test() {
		MAX7219_writeData(MAX7219_REG_DISPLAY_TEST, MAX7219_VAL_TEST_TEST);
	}
#endif

