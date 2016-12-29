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
 *         Implementation of OMA LWM2M / IPSO Illuminance
 * \author
 *         Lovelesh Patel <lovelesh.patel@thingtronics.com>
 *         Amit Sharma <amit.sharma@thingtronics.com>
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"

#ifdef IPSO_ILLUMINANCE
extern const struct ipso_objects_sensor IPSO_ILLUMINANCE;
#endif /* IPSO_ILLUMINANCE */

#ifndef IPSO_ILLUMINANCE_MIN
#define IPSO_ILLUMINANCE_MIN (1 * LWM2M_FLOAT32_FRAC) /* choose appropriate minimum value according to sensor */
#endif

#ifndef IPSO_ILLUMINANCE_MAX
#define IPSO_ILLUMINANCE_MAX (80 * LWM2M_FLOAT32_FRAC) /* choose appropriate maximum value according to sensor */ 
#endif

static struct ctimer periodic_timer;
static int32_t min_illuminance;
static int32_t max_illuminance;
static int read_illuminance(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
illuminance_light(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(read_illuminance(&value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(illuminance_resources,
                /* Illuminance (Current) */
                LWM2M_RESOURCE_CALLBACK(5700, { illuminance_light, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "lux"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_ILLUMINANCE_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_ILLUMINANCE_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_illuminance),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_illuminance),
                );
LWM2M_INSTANCES(illuminance_instances,
                LWM2M_INSTANCE(0, illuminance_resources));
LWM2M_OBJECT(illuminance, 3301, illuminance_instances);
/*---------------------------------------------------------------------------*/
static int
read_illuminance(int32_t *value)
{
#ifdef IPSO_ILLUMINANCE
  int32_t illuminance_light;
  if(IPSO_ILLUMINANCE.read_value == NULL ||
     IPSO_ILLUMINANCE.read_value(&illuminance_light) != 0) {
    return 0;
  }

  /* Convert lux to fix float */
  *value = illuminance_light; /* Use appropriate formula as defined in datasheet */

  if(*value < min_illuminance) {
    min_illuminance = *value;
    lwm2m_object_notify_observers(&illuminance, "/0/5601");
  }
  if(*value > max_illuminance) {
    max_illuminance = *value;
    lwm2m_object_notify_observers(&illuminance, "/0/5602");
  }
  return 1;
#else /* IPSO_ILLUMINANCE */
  return 0;
#endif /* IPSO_ILLUMINANCE */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_ILLUMINANCE_MIN;
  int32_t v;

  /* Only notify when the value has changed since last */
  if(read_illuminance(&v) && v != last_value) {
    last_value = v;
    lwm2m_object_notify_observers(&illuminance, "/0/5700");
  }
  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
ipso_illuminance_init(void)
{
  int32_t v;
  min_illuminance = IPSO_ILLUMINANCE_MAX;
  max_illuminance = IPSO_ILLUMINANCE_MIN;

#ifdef IPSO_ILLUMINANCE
  if(IPSO_ILLUMINANCE.init) {
    IPSO_ILLUMINANCE.init();
  }
#endif /* IPSO_ILLUMIANNCE */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&illuminance);

  /* update temp and min/max + notify any listeners */
  read_illuminance(&v);
  ctimer_set(&periodic_timer, CLOCK_SECOND * 10, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
/** @} */
