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

#endif


