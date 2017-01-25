/*
 * Copyright (c) 2015, Yanzi Networks AB.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    3. Neither the name of the copyright holder nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * \file
 *         An dummy illumination driver as example
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 *         Lovelesh Patel <lovelesh.patel@thingtronics.com>
 */
 /* Pin Details
 		Contiki-subghz/examples/ipso-objects/example-ipso-objects.c
 		find this line : adc_sensors.configure(ANALOG_GROVE_LIGHT, 5);
 		In zoul remote board find ADC1  		
 */

#include "ipso-objects.h"

/***************************************************************************/
//#include "lib/sensors.h"
//#include "dev/soc-adc.h"
//#include "adc-zoul.h"
//#include "adc-sensor.h"


//#include "dev/relay.h"
/*---------------------------------------------------------------------------*/
//#define ADC_PIN              5
//#define SENSOR_READ_INTERVAL (CLOCK_SECOND / 4)
/*****************************************************************************/

static int32_t last_value = 27000;
uint16_t ldr_value;						

/*---------------------------------------------------------------------------*/
static int
read_value(int32_t *value)
{

  /* Insert the code to read analog value of sensor from ADC here */
 //ldr_value = adc_sensor.value(ADC_SENSOR_VALUE);
//		printf("Ldr value before manipulate--->%d\n",ldr_value);			
//	ldr_value = (ldr_value * 100) / 32764 ;
 // printf("LDR Value : %d \n", ldr_value);


	uint8_t data0,data1;

//  if( LTR303_getData(&data0,&data1))
//	printf("Data0=%d\n",data0);
	//printf("Error.........\n");

  	
/* Fix Limit 

  if(ldr_value > 55)
  {
  	relay.value(RELAY_ON);
  }
  else
  {
  	relay.value(RELAY_OFF);
  }
  
 */						
 
  *value = (uint32_t)ldr_value;
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct ipso_objects_sensor example_ipso_analog_input = {
  .read_value = read_value
};
/*---------------------------------------------------------------------------*/
