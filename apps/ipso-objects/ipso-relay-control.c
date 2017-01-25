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
 *
 */

/**
 * \file
 *         Implementation of OMA LWM2M / IPSO Light Control
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 */

#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"

#ifdef IPSO_RELAY_CONTROL
extern const struct ipso_objects_rly_actuator IPSO_RELAY_CONTROL;
#endif /* IPSO_RELAY_CONTROL */
/*---------------------------------------------------------------------------*/
//static unsigned long last_on_time;
//static uint32_t total_on_time;
//static int dim_level = 0;
static uint8_t is_on = 0;
/*---------------------------------------------------------------------------*/
static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_boolean(ctx, outbuf, outsize, is_on ? 1 : 0);
}
/*---------------------------------------------------------------------------*/
static int
write_state(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
  int value;
  size_t len;

  len = ctx->reader->read_boolean(ctx, inbuf, insize, &value);
  if(len > 0) {
    if(value) {
    	
      if(!is_on) {
        is_on = 1;
        IPSO_RELAY_CONTROL.set_on(value);
      }
    } else {
    
      if(is_on) {
        is_on = 0;
        IPSO_RELAY_CONTROL.set_on(value);
        
      }
    }
  }
  return len;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(relay_control_resources,
                LWM2M_RESOURCE_CALLBACK(5850, { read_state, write_state, NULL }),
               // LWM2M_RESOURCE_CALLBACK(5851, { read_dim, write_dim, NULL }),
               // LWM2M_RESOURCE_CALLBACK(5852, { read_on_time, write_on_time, NULL }),
                );
LWM2M_INSTANCES(relay_control_instances,
		LWM2M_INSTANCE(0, relay_control_resources));
LWM2M_OBJECT(relay_control, 3312, relay_control_instances);
/*---------------------------------------------------------------------------*/
void
ipso_relay_control_init(void)
{
#ifdef IPSO_RELAY_CONTROL
  if(IPSO_RELAY_CONTROL.init) {
    IPSO_RELAY_CONTROL.init();
  }
  if(IPSO_RELAY_CONTROL.is_on) {
    is_on = IPSO_RELAY_CONTROL.is_on();
  }
  if(IPSO_RELAY_CONTROL.get_dim_level) {
    //dim_level = IPSO_RELAY_CONTROL.get_dim_level();
    //if(dim_level > 0 && IPSO_RELAY_CONTROL.is_on == NULL) {
    // is_on = 1;
    //}
  }
#endif /* IPSO_RELAY_CONTROL */
 
  lwm2m_engine_register_object(&relay_control);
}
/*---------------------------------------------------------------------------*/
/** @} */
