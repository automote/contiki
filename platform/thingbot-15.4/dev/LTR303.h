/*
   LTR303 illumination sensor library for contiki
   Lovelesh, thingTronics

   The MIT License (MIT)

   Copyright (c) 2016 thingTronics Limited

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

   version 0.1
 */

#ifndef LTR303_h
#define LTR303_h

#include"contiki.h"
#include "board-i2c.h"
#define LTR303_ADDR   0x29 // default slave address

// LTR303 register addrees
#define LTR303_CONTR         0x80 //ALS operation mode control SW reset   R/W
#define LTR303_MEAS_RATE     0x85 //ALS measurement rate in active mode   R/W
#define LTR303_PART_ID       0x86 //Part Number ID and Revision ID        R
#define LTR303_MANUFAC_ID    0x87 //Manufacturer ID			  R
#define LTR303_DATA_CH1_0    0x88 //ALS measurement CH1 data, lower byte  R
#define LTR303_DATA_CH1_1    0x89 //ALS measurement CH1 data, upper byte  R
#define LTR303_DATA_CH0_0    0x8A //ALS measurement CH0 data, lower byte  R
#define LTR303_DATA_CH0_1    0x8B //ALS measurement CH0 data, upper byte  R
#define LTR303_STATUS	     0x8C //ALS new data status                   R
#define LTR303_INTERRUPT     0x8F //Interrupt settings                    R/W
#define LTR303_THRES_UP_0    0x97 //ALS uint8_terrupt upper threshold, lower byte  R/W
#define LTR303_THRES_UP_1    0x98 //ALS uint8_terrupt upper threshold, upper byte  R/W
#define LTR303_THRES_LOW_0   0x99 //ALS uint8_terrupt lower threshold, lower byte  R/W
#define LTR303_THRES_LOW_1   0x9A //ALS uint8_terrupt lower threshold, upper byte  R/W
#define LTR303_INTR_PERS     0x9E //ALS Interrupt persist setting              R/W


void LTR303(void);
// LTR303 object

uint8_t LTR303_begin(void);
// Initialize LTR303 library with default address (0x29)
// Always returns true

uint8_t LTR303_setPowerUp(void);
// Turn on LTR303, begin uint8_tegration
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_setPowerDown(void);
// Turn off LTR303
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_setControl(uint8_t gain, uint8_t reset, uint8_t mode);
// Sets the gain, SW reset and mode of LTR303
// Default value is 0x00
// If gain = 0, device is set to 1X gain (default)
// If gain = 1, device is set to 2X gain
// If gain = 2, device is set to 4X gain
// If gain = 3, device is set to 8X gain
// If gain = 4, invalid
// If gain = 5, invalid
// If gain = 6, device is set to 48X gain
// If gain = 7, device is set to 96X gain
//----------------------------------------
// If reset = false(0), initial start-up procedure not started (default)
// If reset = true(1), initial start-up procedure started
//----------------------------------------
// If mode = false(0), stand-by mode (default)
// If mode = true(1), active mode

uint8_t LTR303_getControl(uint8_t *gain, uint8_t *reset, uint8_t *mode);
// Gets the control register values
// Default value is 0x00
// If gain = 0, device is set to 1X gain (default)
// If gain = 1, device is set to 2X gain
// If gain = 2, device is set to 4X gain
// If gain = 3, device is set to 8X gain
// If gain = 4, invalid
// If gain = 5, invalid
// If gain = 6, device is set to 48X gain
// If gain = 7, device is set to 96X gain
//----------------------------------------
// If reset = false(0), initial start-up procedure not started (default)
// If reset = true(1), initial start-up procedure started
//----------------------------------------
// If mode = false(0), stand-by mode (default)
// If mode = true(1), active mode
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)


 uint8_t LTR303_setMeasurementRate(uint8_t integrationTime, uint8_t measurementRate);
// Sets the uint8_tegration time and measurement rate of the sensor
// uint8_tegrationTime is the measurement time for each ALs cycle
// measurementRate is the uint8_terval between DATA_REGISTERS update
// measurementRate must be set to be equal or greater than uint8_tegrationTime
// Default value is 0x03
// If uint8_tegrationTime = 0, integrationTime will be 100ms (default)
// If uint8_tegrationTime = 1, integrationTime will be 50ms
// If uint8_tegrationTime = 2, integrationTime will be 200ms
// If uint8_tegrationTime = 3, integrationTime will be 400ms
// If uint8_tegrationTime = 4, integrationTime will be 150ms
// If uint8_tegrationTime = 5, integrationTime will be 250ms
// If uint8_tegrationTime = 6, integrationTime will be 300ms
// If uint8_tegrationTime = 7, integrationTime will be 350ms
//------------------------------------------------------
// If measurementRate = 0, measurementRate will be 50ms
// If measurementRate = 1, measurementRate will be 100ms
// If measurementRate = 2, measurementRate will be 200ms
// If measurementRate = 3, measurementRate will be 500ms (default)
// If measurementRate = 4, measurementRate will be 1000ms
// If measurementRate = 5, measurementRate will be 2000ms
// If measurementRate = 6, measurementRate will be 2000ms
// If measurementRate = 7, measurementRate will be 2000ms
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getMeasurementRate(uint8_t *integrationTime, uint8_t *measurementRate);
// Gets the value of Measurement Rate register
// Default value is 0x03
// If uint8_tegrationTime = 0, integrationTime will be 100ms (default)
// If uint8_tegrationTime = 1, integrationTime will be 50ms
// If uint8_tegrationTime = 2, integrationTime will be 200ms
// If uint8_tegrationTime = 3, integrationTime will be 400ms
// If uint8_tegrationTime = 4, integrationTime will be 150ms
// If uint8_tegrationTime = 5, integrationTime will be 250ms
// If uint8_tegrationTime = 6, integrationTime will be 300ms
// If uint8_tegrationTime = 7, integrationTime will be 350ms
//------------------------------------------------------
// If measurementRate = 0, measurementRate will be 50ms
// If measurementRate = 1, measurementRate will be 100ms
// If measurementRate = 2, measurementRate will be 200ms
// If measurementRate = 3, measurementRate will be 500ms (default)
// If measurementRate = 4, measurementRate will be 1000ms
// If measurementRate = 5, measurementRate will be 2000ms
// If measurementRate = 6, measurementRate will be 2000ms
// If measurementRate = 7, measurementRate will be 2000ms
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getPartID(uint8_t  *partID);
// Gets the part number ID and revision ID of the chip
// Default value is 0x0A
// part number ID = 0x0A (default)
// Revision ID = 0x00
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getManufacID(uint8_t *manufacID);
// Gets the Manufacturers ID
// Default value is 0x05
// Returns true (1) if successful, false (0) if there was an I2C error// (Also see getError() below)

uint8_t LTR303_getData(uint8_t *CH0, uint8_t *CH1);
// Gets the 16-bit channel 0 and channel 1 data
// Default value of both channels is 0x00
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getStatus(uint8_t  *valid, uint8_t  *gain, uint8_t  *intrStatus, uint8_t  *dataStatus);
// Gets the status information of LTR303
// Default value is 0x00
// If valid = false(0), Sensor data is valid (default)
// If valid = true(1), Sensor data is invalid
//--------------------------------------------
// If gain = 0, device is set to 1X gain (default)
// If gain = 1, device is set to 2X gain
// If gain = 2, device is set to 4X gain
// If gain = 3, device is set to 8X gain
// If gain = 4, invalid
// If gain = 5, invalid
// If gain = 6, device is set to 48X gain
// If gain = 7, device is set to 96X gain
//---------------------------------------------
// If uint8_trStatus = false(0), INTR in inactive (default)
// If uint8_trStatus = true(1), INTR in active
//---------------------------------------------
// If dataStatus = false(0), OLD data (already read) (default)
// If dataStatus = true(1), NEW data
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_setInterruptControl(uint8_t  intrMode, uint8_t polarity);
// Sets up uint8_terrupt operations
// Default value is 0x08
// If uint8_trMode = false(0), INT pin is inactive (default)
// If uint8_trMode = true(1), INT pin is active
//------------------------------------------------------
// If polarity = false(0), INT pin is active at logic 0 (default)
// If polarity = true(1), INT pin is active at logic 1
//------------------------------------------------------
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getInterruptControl(uint8_t  *polarity, uint8_t  *intrMode);
// Sets up uint8_terrupt operations
// Default value is 0x08
// If polarity = false(0), INT pin is active at logic 0 (default)
// If polarity = true(1), INT pin is active at logic 1
//------------------------------------------------------
// If uint8_trMode = false(0), INT pin is inactive (default)
// If uint8_trMode = true(1), INT pin is active
//------------------------------------------------------
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_setThreshold(unsigned int upperLimit, unsigned int lowerLimit);
// Sets the upper limit and lower limit of the threshold
// Default value of upper threshold is 0xFF and lower threshold is 0x00
// Both the threshold are 16-bit uint8_teger values
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getThreshold(unsigned int *upperLimit, unsigned int *lowerLimit);
// Gets the upper limit and lower limit of the threshold
// Default value of upper threshold is 0xFF and lower threshold is 0x00
// Both the threshold are 16-bit uint8_teger values
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_setIntrPersist(uint8_t persist);
// Sets the uint8_terrupt persistance i.e. controls the N number of times the 
// measurement data is outside the range defined by upper and lower threshold
// Default value is 0x00
// If persist = 0, every sensor value out of threshold range (default)
// If persist = 1, every 2 consecutive value out of threshold range
// If persist = 2, every 3 consecutive value out of threshold range
// If persist = 3, every 4 consecutive value out of threshold range
// If persist = 4, every 5 consecutive value out of threshold range
// If persist = 5, every 6 consecutive value out of threshold range
// If persist = 6, every 7 consecutive value out of threshold range
// If persist = 7, every 8 consecutive value out of threshold range
// If persist = 8, every 9 consecutive value out of threshold range
// If persist = 9, every 10 consecutive value out of threshold range
// If persist = 10, every 11 consecutive value out of threshold range
// If persist = 11, every 12 consecutive value out of threshold range
// If persist = 12, every 13 consecutive value out of threshold range
// If persist = 13, every 14 consecutive value out of threshold range
// If persist = 14, every 15 consecutive value out of threshold range
// If persist = 15, every 16 consecutive value out of threshold range
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getIntrPersist(uint8_t  *persist);
// Gets the uint8_terrupt persistance i.e. controls the N number of times the measurement data is outside the range defined by upper and lower threshold
// Default value is 0x00
// If persist = 0, every sensor value out of threshold range (default)
// If persist = 1, every 2 consecutive value out of threshold range
// If persist = 2, every 3 consecutive value out of threshold range
// If persist = 3, every 4 consecutive value out of threshold range
// If persist = 4, every 5 consecutive value out of threshold range
// If persist = 5, every 6 consecutive value out of threshold range
// If persist = 6, every 7 consecutive value out of threshold range
// If persist = 7, every 8 consecutive value out of threshold range
// If persist = 8, every 9 consecutive value out of threshold range
// If persist = 9, every 10 consecutive value out of threshold range
// If persist = 10, every 11 consecutive value out of threshold range
// If persist = 11, every 12 consecutive value out of threshold range
// If persist = 12, every 13 consecutive value out of threshold range
// If persist = 13, every 14 consecutive value out of threshold range
// If persist = 14, every 15 consecutive value out of threshold range
// If persist = 15, every 16 consecutive value out of threshold range
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() below)

uint8_t LTR303_getLux(uint8_t  gain, uint8_t  integrationTime, unsigned int CH0, unsigned int CH1, double *lux);
// Convert raw data to lux
// gain: 0 (1X) or 7 (96X), see getControl()
// uint8_tegrationTime: integration time in ms, from getMeasurementRate()
// CH0, CH1: results from getData()
// lux will be set to resulting lux calculation
// returns true (1) if calculation was successful
// returns false (0) AND lux = 0.0 IF EITHER SENSOR WAS SATURATED (0XFFFF)

uint8_t LTR303_getError(void);
// If any library command fails, you can retrieve an extended
// error code using this command. Errors are from the wire library: 
// 0 = Success
// 1 = Data too long to fit in transmit buffer
// 2 = Received NACK on transmit of address
// 3 = Received NACK on transmit of data
// 4 = Other error



uint8_t LTR303_readByte(uint8_t  address, uint8_t *value);
// Reads a byte from a LTR303 address
// Address: LTR303 address (0 to 15)
// Value will be set to stored byte
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() above)

uint8_t LTR303_writeByte(uint8_t  address, uint8_t  value);
// Write a byte to a LTR303 address
// Address: LTR303 address (0 to 15)
// Value: byte to write to address
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() above)

uint8_t LTR303_readUInt(uint8_t  address, unsigned int *value);
// Reads an unsigned uint8_teger (16 bits) from a LTR303 address (low byte first)
// Address: LTR303 address (0to 15), low byte first
// Value will be set to stored unsigned uint8_teger
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() above)

uint8_t LTR303_writeUInt(uint8_t address, unsigned int value);
// Write an unsigned uint8_teger (16 bits) to a LTR303 address (low byte first)
// Address: LTR303 address (0 to 15), low byte first
// Value: unsigned uint8_t to write to address
// Returns true (1) if successful, false (0) if there was an I2C error
// (Also see getError() above)

uint8_t _i2c_address;

uint8_t _error;





#endif
