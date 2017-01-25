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
 *         Implementation of OMA LWM2M / IPSO LDR
 * \author
 *         Lovelesh Patel <lovelesh.patel@thingtronics.com>
 *         Amit Sharma <amit.sharma@thingtronics.com>
	   
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"

#ifdef IPSO_3202
extern const struct ipso_objects_sensor IPSO_3202;
#endif /* IPSO_ANALOG_INPUT */

#ifndef IPSO_LDR_MIN
#define IPSO_LDR_MIN (1 * LWM2M_FLOAT32_FRAC) /* choose appropriate minimum value according to sensor */
#endif

#ifndef IPSO_LDR_MAX
#define IPSO_LDR_MAX (80 * LWM2M_FLOAT32_FRAC) /* choose appropriate maximum value according to sensor */ 
#endif

static struct ctimer periodic_timer;
static int32_t min_ldr;
static int32_t max_ldr;
static int read_ldr_input(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
ldr_input(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
printf("Enter into the ipso object-->ldr_input\n");
  if(read_ldr_input(&value)) {
//printf("leaving due to if the ipso object-->ldr_input\n");
	printf("in ldr_input writing to ipso object..%d\n",value);
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
//printf("Enter into the ipso object-->read_analog_init function\n");
  return 0;
}

static int
ldr_name(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
	char s[10]="ldr";
 return ctx->writer->write_string(ctx, outbuf, outsize,
                                         s ,4);

		




}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(ldr_resources,
                /* ldr Input (Current) */
                LWM2M_RESOURCE_CALLBACK(5600, {ldr_input, NULL, NULL }),
                /* Sensor Type */
                LWM2M_RESOURCE_CALLBACK(5751, {ldr_name,NULL,NULL}),
		/* Sensor Application Type */
		LWM2M_RESOURCE_STRING(5750, "Ambient Light"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_LDR_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_LDR_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_ldr),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_ldr),
                );		
LWM2M_INSTANCES(ldr_instances,
		LWM2M_INSTANCE(0, ldr_resources));
LWM2M_OBJECT(ldr, 3202, ldr_instances);
/*---------------------------------------------------------------------------*/
static int
read_ldr_input(int32_t *value)
{
//printf("Enter into the ipso object-->read_analog_input function\n");
#ifdef IPSO_3202
  int32_t ldr_input;
  if(IPSO_3202.read_value == NULL ||
     IPSO_3202.read_value(&ldr_input) != 0) {
    return 0;
  }
//printf("Enter into the ipso object-->read_analog_input function\n");
  /* Convert LDR value to fix float */
  *value = ldr_input; /* Use appropriate formula as defined in datasheet of LDR */
printf("in ipso ldr reading....ldr_input=%d , value=%d\n",ldr_input , *value);

  if(*value < min_ldr) {
    min_ldr = *value;
    lwm2m_object_notify_observers(&ldr, "/0/5601");
  }
  if(*value > max_ldr) {
    max_ldr = *value;
    lwm2m_object_notify_observers(&ldr, "/0/5602");
  }
//printf("leaving function the ipso object-->read_analog_input function\n");
  return 1;
#else /* IPSO_ANALOG_INPUT */
  return 0;
#endif /* IPSO_ANALOG_INPUT */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_LDR_MIN;
  int32_t v;
//printf("Enter into the ipso object-->read_handle_periodic\n");
  /* Only notify when the value has changed since last */
  if(read_ldr_input(&v) && v != last_value) {
    last_value = v;
    lwm2m_object_notify_observers(&ldr, "/0/5600");
  }
  ctimer_reset(&periodic_timer);
//printf("Leaving the ipso object-->handle_periodic\n");
}
/*---------------------------------------------------------------------------*/
void
ipso_ldr_init(void)
{
  int32_t v;
  min_ldr = IPSO_LDR_MIN;
  max_ldr = IPSO_LDR_MAX;
//printf("Enter into the ipso object-->read_analog_init function\n");
	
#ifdef IPSO_3202
  if(IPSO_3202.init) {
    IPSO_3202.init();
  }
#endif /* IPSO_ANALOG_INPUT */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&ldr);

  /* update temp and min/max + notify any listeners */
  read_ldr_input(&v);
  //ctimer_set(&periodic_timer, CLOCK_SECOND * 10, handle_periodic_timer, NULL);
ctimer_set(&periodic_timer, CLOCK_SECOND * 10, handle_periodic_timer, NULL);
//printf("Leaving function the ipso object-->read_analog_init function\n");
}
/*---------------------------------------------------------------------------*/
/** @} */
