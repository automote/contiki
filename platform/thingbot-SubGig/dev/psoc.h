/*
	psoc
 */

#ifndef PSOC_H
#define PSOC_H

#include"contiki.h"
#include "board-i2c.h"

#define PSOC_ADDR   0x08 // PSOC slave address

bool sensor_init(void);

bool PSOC_read(uint8_t* value, uint8_t len);

bool PSOC_write(uint8_t* value, uint8_t len);

#endif
