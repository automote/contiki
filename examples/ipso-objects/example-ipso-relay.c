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
 /**
 			Pin Details
 			/contiki-subghz/platform/zoul/dev/relay.h
 			PIN 4			// zoul remote borad SCLK1
 			PORT C
 */
 
#include "ipso-objects.h"
//#include "dev/relay.h"
//#include "lib/sensors.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
static int
is_on()
{
 	int status;
//	status=relay.status(SENSORS_ACTIVE);
	return status;
}
/*--------------------------------------------------------------------------------*/
static int set_on(int status)
{
	uint32_t res;
		if(status)
		{
//			res = relay.value(RELAY_OFF);
		}
		else
		{
//			res = relay.value(RELAY_ON);
		}
return res;
}
/*---------------------------------------------------------------------------*/
const struct ipso_objects_actuator example_ipso_relay_control = {
  .is_on = is_on,
  .set_on = set_on
};
/*---------------------------------------------------------------------------*/
