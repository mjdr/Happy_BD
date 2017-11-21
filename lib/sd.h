#pragma once

#include "spi.h"

#define SS_PORT PORTD
#define SS_PIN 2

#define SD_CMD0 0x40
#define SD_CMD1 0x41

//ERRORS
// init
#define SD_CANT_GET_RESPOND_CMD0 1
#define SD_CANT_GET_RESPOND_CMD1 2
 


char SD_init();


