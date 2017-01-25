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

#include"LTR303.h"
//#include"board-i2c.h"
#include"math.h"


void LTR303(void) {
	// LTR303 object
}

uint8_t LTR303_begin(void) {
	// Initialize LTR303 library with default address (0x39)
	// Always returns true

	_i2c_address = LTR303_ADDR;
		board_i2c_wakeup();
		board_i2c_select(BOARD_I2C_INTERFACE_0,_i2c_address);
		return(true);
}

uint8_t LTR303_setPowerUp(void) {
	// Turn on LTR303, begin integrations
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)

	// Write 0x03 (reset = 1 & mode = 1) to command byte (power on)
	return(LTR303_writeByte(LTR303_CONTR,0x03));
}

uint8_t LTR303_setPowerDown(void) {
	// Turn off LTR303
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)

	// Clear command byte (reset = 0 & mode = 0)(power off)
	return(LTR303_writeByte(LTR303_CONTR,0x00));
}

uint8_t LTR303_setControl(uint8_t gain, uint8_t reset , uint8_t mode ) {
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
	
	uint8_t control = 0x00;
	
	// sanity check for gain
	if (gain > 3 && gain < 6) {
		gain = 0x00;
	}
	else if(gain > 7) {
		gain = 0x00;
	}
	
	// control byte logic
	control |= gain << 2;
	if(reset) {
		control |= 0x02;
	}
	
	if(mode) {
		control |= 0x01;
	}
	
	return(LTR303_writeByte(LTR303_CONTR,control));
}			
			
uint8_t LTR303_getControl(uint8_t *gain, uint8_t *reset, uint8_t *mode) {
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
	
	uint8_t control;
	
	// Reading the control byte
	if(LTR303_readByte(LTR303_CONTR, &control)) {
		// Extract gain
		*gain = (control & 0x1C) >> 2;
		
		// Extract reset
		*reset = (control & 0x02) ? true : false; 
		
		// Extract mode
		*mode = (control & 0x01) ? true : false;
		
		// return if successful
		return(true);
	}
	return(false);
}

uint8_t LTR303_setMeasurementRate(uint8_t integrationTime, uint8_t measurementRate ) {
	// Sets the integration time and measurement rate of the sensor
	// integrationTime is the measurement time for each ALs cycle
	// measurementRate is the interval between DATA_REGISTERS update
	// measurementRate must be set to be equal or greater than integrationTime
	// Default value is 0x03
	// If integrationTime = 0, integrationTime will be 100ms (default)
	// If integrationTime = 1, integrationTime will be 50ms
	// If integrationTime = 2, integrationTime will be 200ms
	// If integrationTime = 3, integrationTime will be 400ms
	// If integrationTime = 4, integrationTime will be 150ms
	// If integrationTime = 5, integrationTime will be 250ms
	// If integrationTime = 6, integrationTime will be 300ms
	// If integrationTime = 7, integrationTime will be 350ms
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
	
	uint8_t measurement = 0x00;
	
	// Perform sanity checks
	if(integrationTime > 0x07) {
		integrationTime = 0x00;
	}
	
	if(measurementRate > 0x07) {
		measurementRate = 0x00;
	}
	
	measurement |= integrationTime << 3;
	measurement |= measurementRate;
	
	return(LTR303_writeByte(LTR303_MEAS_RATE, measurement));
}

uint8_t LTR303_getMeasurementRate(uint8_t *integrationTime, uint8_t *measurementRate) {
	// Gets the value of Measurement Rate register
	// Default value is 0x03
	// If integrationTime = 0, integrationTime will be 100ms (default)
	// If integrationTime = 1, integrationTime will be 50ms
	// If integrationTime = 2, integrationTime will be 200ms
	// If integrationTime = 3, integrationTime will be 400ms
	// If integrationTime = 4, integrationTime will be 150ms
	// If integrationTime = 5, integrationTime will be 250ms
	// If integrationTime = 6, integrationTime will be 300ms
	// If integrationTime = 7, integrationTime will be 350ms
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
			
	uint8_t measurement = 0x00;
	
	// Reading the measurement byte
	if(LTR303_readByte(LTR303_MEAS_RATE, &measurement)) {
		// Extract integration Time
		*integrationTime = (measurement & 0x38) >> 3;
		
		// Extract measurement Rate
		*measurementRate = measurement & 0x07; 
		
		// return if successful
		return(true);
	}
	return(false);		
}

uint8_t LTR303_getPartID(uint8_t *partID) {
	// Gets the part number ID and revision ID of the chip
	// Default value is 0x0A
	// part number ID = 0x0A (default)
	// Revision ID = 0x00
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	return(LTR303_readByte(LTR303_PART_ID, partID));
		
		
	
}

uint8_t LTR303_getManufacID(uint8_t *manufacID) {
	// Gets the Manufacturers ID
	// Default value is 0x05
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	return(LTR303_readByte(LTR303_MANUFAC_ID, manufacID));
}

uint8_t LTR303_getData(uint8_t *CH0, uint8_t *CH1) {
	// Gets the 16-bit channel 0 and channel 1 data
	// Default value of both channels is 0x00
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	(LTR303_readByte(LTR303_DATA_CH0_0,CH0) && LTR303_readByte(LTR303_DATA_CH1_0,CH1));
		printf("in get data function --->ch0-->%d  ch1-->%d\n",*CH0,*CH1);
		return 1;
}

uint8_t LTR303_getStatus(uint8_t *valid, uint8_t *gain, uint8_t *intrStatus, uint8_t *dataStatus) {
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
	// If intrStatus = false(0), INTR in inactive (default)
	// If intrStatus = true(1), INTR in active
	//---------------------------------------------
	// If dataStatus = false(0), OLD data (already read) (default)
	// If dataStatus = true(1), NEW data
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	uint8_t status = 0x00;
	
	// Reading the status byte
	if(LTR303_readByte(LTR303_STATUS, &status)) {
		// Extract validity
		*valid = (status & 0x80) ? true : false;
	
		// Extract gain
		*gain = (status & 0x70) >> 4;
	
		// Extract interrupt status
		*intrStatus = (status & 0x08) ? true : false;
	
		// Extract data status
		*dataStatus = (status & 0x04) ? true : false;
		
		// return if successful
		return(true);
	}
	return(false);
}

uint8_t LTR303_setInterruptControl(uint8_t intrMode, uint8_t polarity) {
	// Sets up interrupt operations
	// Default value is 0x08
	// If intrMode = false(0), INT pin is inactive (default)
	// If intrMode = true(1), INT pin is active
	//------------------------------------------------------
	// If polarity = false(0), INT pin is active at logic 0 (default)
	// If polarity = true(1), INT pin is active at logic 1
	//------------------------------------------------------
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	uint8_t intrControl = 0x00;
	
	intrControl |= polarity << 2;
	intrControl |= intrMode << 1;
	
	return(LTR303_writeByte(LTR303_INTERRUPT, intrControl));
}

uint8_t LTR303_getInterruptControl(uint8_t *polarity, uint8_t *intrMode) {
	// Sets up interrupt operations
	// Default value is 0x08
	// If polarity = false(0), INT pin is active at logic 0 (default)
	// If polarity = true(1), INT pin is active at logic 1
	//------------------------------------------------------
	// If intrMode = false(0), INT pin is inactive (default)
	// If intrMode = true(1), INT pin is active
	//------------------------------------------------------
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	uint8_t intrControl = 0x00;
	
	// Reading the interrupt byte
	if(LTR303_readByte(LTR303_INTERRUPT, &intrControl)) {
		// Extract polarity
		*polarity = (intrControl & 0x04) ? true : false;
	
		// Extract mode
		*intrMode = (intrControl & 0x02) ? true : false;
	
		// return if successful
		return(true);
	}
	return(false);
}

uint8_t LTR303_setThreshold(unsigned int upperLimit, unsigned int lowerLimit) {
	// Sets the upper limit and lower limit of the threshold
	// Default value of upper threshold is 0xFF and lower threshold is 0x00
	// Both the threshold are 16-bit integer values
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
	
	return(LTR303_writeUInt(LTR303_THRES_UP_0,upperLimit) && LTR303_writeUInt(LTR303_THRES_LOW_0,lowerLimit));
}

uint8_t LTR303_getThreshold(unsigned int *upperLimit, unsigned int *lowerLimit) {
	// Gets the upper limit and lower limit of the threshold
	// Default value of upper threshold is 0xFF and lower threshold is 0x00
	// Both the threshold are 16-bit integer values
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() below)
			
	return(LTR303_readUInt(LTR303_THRES_UP_0,upperLimit) && LTR303_readUInt(LTR303_THRES_LOW_0,lowerLimit));		
}

uint8_t LTR303_setIntrPersist(uint8_t persist) {
	// Sets the interrupt persistance i.e. controls the N number of times the 
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
	
	// sanity check
	if(persist > 15) {
		persist = 0x00;
	}
			
	return(LTR303_writeByte(LTR303_INTR_PERS,persist));
}

uint8_t LTR303_getIntrPersist(uint8_t *persist) {
	// Gets the interrupt persistance i.e. controls the N number of times the measurement data is outside the range defined by upper and lower threshold
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
	
	return(LTR303_readByte(LTR303_INTR_PERS,persist));
}

// Get the right lux algorithm
uint8_t LTR303_getLux(uint8_t gain, uint8_t integrationTime, unsigned int CH0, unsigned int CH1, double *lux) {
	// Convert raw data to lux
	// gain: 0 (1X) or 7 (96X), see getControl()
	// integrationTime: integration time in ms, from getMeasurementRate()
	// CH0, CH1: results from getData()
	// lux will be set to resulting lux calculation
	// returns true (1) if calculation was successful
	// returns false (0) AND lux = 0.0 IF EITHER SENSOR WAS SATURATED (0XFFFF)

	double ratio, d0, d1;

	// Determine if either sensor saturated (0xFFFF)
	// If so, abandon ship (calculation will not be accurate)
	if ((CH0 == 0xFFFF) || (CH1 == 0xFFFF)) {
		*lux = 0.0;
		return(false);
	}

	// Convert from unsigned integer to floating point
	d0 = CH0; d1 = CH1;

	// We will need the ratio for subsequent calculations
	ratio = d1 / d0;

	// Normalize for integration time
	d0 *= (402.0/integrationTime);
	d1 *= (402.0/integrationTime);

	// Normalize for gain
	if (!gain) {
		d0 *= 16;
		d1 *= 16;
	}

	// Determine lux per datasheet equations:
	if (ratio < 0.5) {
		*lux = 0.0304 * d0 - 0.062 * d0 * pow(ratio,1.4);
		return(true);
	}

	if (ratio < 0.61) {
		*lux = 0.0224 * d0 - 0.031 * d1;
		return(true);
	}

	if (ratio < 0.80) {
		*lux = 0.0128 * d0 - 0.0153 * d1;
		return(true);
	}

	if (ratio < 1.30) {
		*lux = 0.00146 * d0 - 0.00112 * d1;
		return(true);
	}

	// if (ratio > 1.30)
	*lux = 0.0;
	return(true);
}

uint8_t LTR303_getError(void) {
	// If any library command fails, you can retrieve an extended
	// error code using this command. Errors are from the wire library: 
	// 0 = Success
	// 1 = Data too long to fit in transmit buffer
	// 2 = Received NACK on transmit of address
	// 3 = Received NACK on transmit of data
	// 4 = Other error

	return(_error);
}

// Private functions:

uint8_t LTR303_readByte(uint8_t address, uint8_t *value) {
	// Reads a byte from a LTR303 address
	// Address: LTR303 address (0 to 15)
	// Value will be set to stored byte
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() above)

	// Check if sensor present for read
	
	uint8_t temp;
	board_i2c_select(BOARD_I2C_INTERFACE_0,_i2c_address);

	temp=board_i2c_read(&address,1);
	

	// Read requested byte
//	if (temp)
	{
	//	if(board_i2c_read(value,1))
			board_i2c_read(value,1);
			printf("value in ltr function-->%d\n",*value);
			return(true);
	}
	return(false);
}

uint8_t LTR303_writeByte(uint8_t address, uint8_t value) {
	// Write a byte to a LTR303 address
	// Address: LTR303 address (0 to 15)
	// Value: byte to write to address
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() above)

//	Wire.beginTransmission(_i2c_address);
	board_i2c_select(BOARD_I2C_INTERFACE_0,_i2c_address);
	if(board_i2c_write_single(address))
		if(board_i2c_write_single(value))
			return(true);
	return(false);


}

uint8_t LTR303_readUInt(uint8_t address, unsigned int *value) {
	// Reads an unsigned integer (16 bits) from a LTR303 address (low byte first)
	// Address: LTR303 address (0 to 15), low byte first
	// Value will be set to stored unsigned integer
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() above)

	uint8_t high, low;
	
	// Check if sensor present for read
/*	Wire.beginTransmission(_i2c_address);
	Wire.write(address);
	_error = Wire.endTransmission();

	// Read two bytes (low and high)
	if (_error == 0)
	{
		Wire.requestFrom(_i2c_address,2);
		if (Wire.available() == 2)
		{
			low = Wire.read();
			high = Wire.read();
			// Combine bytes into unsigned int
			value = word(high,low);
			return(true);
		}
	}*/	
	return(false);
}

uint8_t LTR303_writeUInt(uint8_t address, unsigned int value) {
	// Write an unsigned integer (16 bits) to a LTR303 address (low byte first)
	// Address: LTR303 address (0 to 15), low byte first
	// Value: unsigned int to write to address
	// Returns true (1) if successful, false (0) if there was an I2C error
	// (Also see getError() above)

	// Split int into lower and upper bytes, write each byte
//	if (writeByte(address,lowByte(value)) 
//		&& writeByte(address + 1,highByte(value)))
		return(true);

	return(false);
}

