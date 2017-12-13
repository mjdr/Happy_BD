#include "soft_spi.h"
#include "uart.h"
#include "writer.h"


#define SCK_ON  SCK_PORT |= (1 << SCK_PIN)
#define SCK_OFF SCK_PORT &= ~(1 << SCK_PIN)

#define MOSI_ON  MOSI_PORT |= (1 << MOSI_PIN)
#define MOSI_OFF MOSI_PORT &= ~(1 << MOSI_PIN)


void SOFTSPI_init(){
	SCK_PORT |= (1 << SCK_PIN);
	SCK_DDR |= (1 << SCK_PIN);
	MOSI_DDR |= (1 << MOSI_PIN);

}
void SOFTSPI_send(uint8_t data) {

	#ifdef DEBUG
		WRITER_writeString("SOFT_SPI: ", "\n\r");
		WRITER_writeHex16(&UART_trasmit, data);
		WRITER_writeString(&UART_trasmit, "\n\r");
	#endif

	for(uint8_t i = 0;i < 8;i++){
		if(data & 0x80)
			MOSI_ON;
		else
			MOSI_OFF;

		SCK_OFF;
		_delay_us(10);
		SCK_ON;
		_delay_us(10);

		data <<= 1;
	}

}


