/*
 * Copyright (c) 2015, Yanzi Networks AB.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \addtogroup ipso-objects
 * @{
 */

/**
 * \file
 *         Implementation of OMA LWM2M / IPSO Analog Input
 * \author
 *         Lovelesh Patel <lovelesh.patel@thingtronics.com>
 *         Amit Sharma <amit.sharma@thingtronics.com>
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"

#ifdef IPSO_ANALOG_INPUT
extern const struct ipso_objects_sensor IPSO_ANALOG_INPUT;
#endif /* IPSO_ANALOG_INPUT */

#ifndef IPSO_ANALOG_INPUT_MIN
#define IPSO_ANALOG_INPUT_MIN (1 * LWM2M_FLOAT32_FRAC) /* choose appropriate minimum value according to sensor */
#endif

#ifndef IPSO_ANALOG_INPUT_MAX
#define IPSO_ANALOG_INPUT_MAX (80 * LWM2M_FLOAT32_FRAC) /* choose appropriate maximum value according to sensor */ 
#endif

static struct ctimer periodic_timer;
static int32_t min_analog_input;
static int32_t max_analog_input;
static int read_analog_input(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
analog_input_light(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
printf("Enter into the ipso object-->read_analog_input_light\n");
  if(read_analog_input(&value)) {
printf("leaving due to if the ipso object-->read_analog_input_light\n");
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
printf("Enter into the ipso object-->read_analog_init function\n");
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(analog_input_resources,
                /* Analog Input (Current) */
                LWM2M_RESOURCE_CALLBACK(5600, { analog_input_light, NULL, NULL }),
                /* Sensor Type */
                LWM2M_RESOURCE_STRING(5751, "LDR"),
		/* Sensor Application Type */
		LWM2M_RESOURCE_STRING(5750, "Ambient Light"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_ANALOG_INPUT_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_ANALOG_INPUT_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_analog_input),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_analog_input),
                );		
LWM2M_INSTANCES(analog_input_instances,
		LWM2M_INSTANCE(0, analog_input_resources));
LWM2M_OBJECT(analog_input, 3202, analog_input_instances);
/*---------------------------------------------------------------------------*/
static int
read_analog_input(int32_t *value)
{
#ifdef IPSO_ANALOG_INPUT
  int32_t analog_input_light;
  if(IPSO_ANALOG_INPUT.read_value == NULL ||
     IPSO_ANALOG_INPUT.read_value(&analog_input_light) != 0) {
    return 0;
  }
printf("Enter into the ipso object-->read_analog_input function\n");
  /* Convert LDR value to fix float */
  *value = analog_input_light; /* Use appropriate formula as defined in datasheet of LDR */

  if(*value < min_analog_input) {
    min_analog_input = *value;
    lwm2m_object_notify_observers(&analog_input, "/0/5601");
  }
  if(*value > max_analog_input) {
    max_analog_input = *value;
    lwm2m_object_notify_observers(&analog_input, "/0/5602");
  }
printf("leaving function the ipso object-->read_analog_input function\n");
  return 1;
#else /* IPSO_ANALOG_INPUT */
  return 0;
#endif /* IPSO_ANALOG_INPUT */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_ANALOG_INPUT_MIN;
  int32_t v;
printf("Enter into the ipso object-->read_handle_periodic\n");
  /* Only notify when the value has changed since last */
  if(read_analog_input(&v) && v != last_value) {
    last_value = v;
    lwm2m_object_notify_observers(&analog_input, "/0/5600");
  }
  ctimer_reset(&periodic_timer);
printf("Leaving the ipso object-->handle_periodic\n");
}
/*---------------------------------------------------------------------------*/
void
ipso_analog_input_init(void)
{
  int32_t v;
  min_analog_input = IPSO_ANALOG_INPUT_MAX;
  max_analog_input = IPSO_ANALOG_INPUT_MIN;
printf("Enter into the ipso object-->read_analog_init function\n");
	
#ifdef IPSO_ANALOG_INPUT
  if(IPSO_ANALOG_INPUT.init) {
   IPSO_ANALOG_INPUT.init();
  }
#endif /* IPSO_ANALOG_INPUT */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&analog_input);

  /* update temp and min/max + notify any listeners */
  read_analog_input(&v);
  //ctimer_set(&periodic_timer, CLOCK_SECOND * 10, handle_periodic_timer, NULL);
ctimer_set(&periodic_timer, CLOCK_SECOND * 100, handle_periodic_timer, NULL);
printf("Leaving function the ipso object-->read_analog_init function\n");
}
/*---------------------------------------------------------------------------*/
/** @} */
