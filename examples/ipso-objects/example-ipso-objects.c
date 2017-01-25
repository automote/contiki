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
 *
 */

/**
 * \file
 *      OMA LWM2M and IPSO Objects example.
 * \author
 *      Joakim Eriksson, joakime@sics.se
 *      Niclas Finne, nfi@sics.se
 */

#include "contiki.h"
#include "lwm2m-engine.h"
#include "ipso-objects.h"

/********************************************************/
// For adc and relay

#include "lib/sensors.h"
#include "dev/psoc.h"
#include "dev/psoc-int.h"
//#include "dev/soc-adc.h"
//#include "adc-zoul.h"
//#include "adc-sensor.h"
//#include "dev/LTR303.h"

//#include "dev/relay.h"
uint8_t gain;     // Gain setting, values = 0-7 
uint8_t integrationTime;  // Integration ("shutter") time in milliseconds
uint8_t measurementRate;  // Interval between DATA_REGISTERS update

/********************************************************/

#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"

#ifndef REGISTER_WITH_LWM2M_BOOTSTRAP_SERVER
#define REGISTER_WITH_LWM2M_BOOTSTRAP_SERVER 0
#endif

#ifndef REGISTER_WITH_LWM2M_SERVER
#define REGISTER_WITH_LWM2M_SERVER 1
#endif

#ifndef LWM2M_SERVER_ADDRESS
#define LWM2M_SERVER_ADDRESS "fd00::1"
#endif

#define MAX_3311_PSOC_RESOURCE 6 //change according to how many instance u want of this particuar resources

static struct ctimer periodic_timer;
extern const struct ipso_objects_rly_actuator IPSO_RELAY_CONTROL;
//extern const struct ipso_objects_sensor IPSO_LDR;
extern const struct ipso_objects_sensor IPSO_3202;
extern const struct ipso_objects_actuator IPSO_light_control;

PROCESS(example_ipso_objects, "IPSO object example");
AUTOSTART_PROCESSES(&example_ipso_objects);
/*---------------------------------------------------------------------------*/
static void
setup_lwm2m_servers(void)
{
printf("Enter into setup_lwm2m_servers..\n");
#ifdef LWM2M_SERVER_ADDRESS
  uip_ipaddr_t addr;
  if(uiplib_ipaddrconv(LWM2M_SERVER_ADDRESS, &addr)) {
    lwm2m_engine_register_with_bootstrap_server(&addr, 0);
    lwm2m_engine_register_with_server(&addr, 0);
  }
#endif /* LWM2M_SERVER_ADDRESS */

  lwm2m_engine_use_bootstrap_server(REGISTER_WITH_LWM2M_BOOTSTRAP_SERVER);
  lwm2m_engine_use_registration_server(REGISTER_WITH_LWM2M_SERVER);
printf("Leaving from setup_lwm2m_servers..\n");
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  printf("Enter into the handle periofdic functionn of example...\n");
	int32_t temp;
	
	//temp=adc_sensors.value(ANALOG_GROVE_LIGHT);
	//		IPSO_3202.read_value(&temp);
		//if(temp<55 && !(IPSO_RELAY_CONTROL.is_on()))
		//		        IPSO_RELAY_CONTROL.set_on(1);

		//if(temp>=55 && (IPSO_RELAY_CONTROL.is_on()))
		//			IPSO_RELAY_CONTROL.set_on(0);

				
				
ctimer_reset(&periodic_timer);
}
/*==================================================================*/
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_ipso_objects, ev, data)
{
  PROCESS_BEGIN();

  PROCESS_PAUSE();

  PRINTF("Starting IPSO objects example\n");
 /*-------------------------------------------------------------------------*/
 
 /* Use pin number not mask, for example if using the PA5 pin then use 5 */
 
 // adc_sensor.configure(SENSORS_ACTIVE, 1);
  
  //SENSORS_ACTIVATE(relay); 
	uint8_t ID,time;
//	LTR303_begin();
//	LTR303_getPartID(&ID);
//	gain=0;
//	LTR303_setControl(gain,false,false);
//	LTR303_setMeasurementRate(time,3);
//		LTR303_setPowerUp();
	
	





  
 /*-------------------------------------------------------------------------*/
  /* Initialize the OMA LWM2M engine */
  lwm2m_engine_init();

  /* Register default LWM2M objects */
  lwm2m_engine_register_default_objects();

  /* Register default IPSO objects */
  ipso_objects_init();
  psoc_int_pin.configure(SENSORS_HW_INIT, 1);

  setup_lwm2m_servers();
 ctimer_set(&periodic_timer, CLOCK_SECOND * 60, handle_periodic_timer, NULL);

  while(1) {
    PROCESS_WAIT_EVENT();
  }

  PROCESS_END();
}
