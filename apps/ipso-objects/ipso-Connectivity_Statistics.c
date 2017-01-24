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
 *         Amar Garg<amar.garg@thingtronics.com>
 */

#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"


extern int tx_Data;
 extern int rx_Data;
 
/*---------------------------------------------------------------------------*/
static int 
tx_data(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	
	tx_Data++;	
	return ctx->writer->write_int(ctx, outbuf, outsize,tx_Data);
}
/*---------------------------------------------------------------------------*/
static int
rx_data(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	rx_Data++;
       
	return ctx->writer->write_int(ctx, outbuf, outsize,rx_Data);

}
/*--------------------------------------------------------------------------*/
static int 
max_msg_size(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint16_t max_size=127;


	return ctx->writer->write_int(ctx, outbuf, outsize,max_size);
}
/*--------------------------------------------------------------------------*/
static int 
avg_msg_size(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint16_t avg_size=50;




	return ctx->writer->write_int(ctx,outbuf,outsize,avg_size);
}
/*---------------------------------------------------------------------------*/
static int
start_reset(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
		




	//return ctx->writer->write_string(ctx, outbuf,outsize,router_ip_address,13);
}
/*---------------------------------------------------------------------------*/

LWM2M_RESOURCES(connectivity_statistics_resources,
                LWM2M_RESOURCE_CALLBACK(2, { tx_data, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(3, { rx_data, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(4, { max_msg_size, NULL, NULL }),
		LWM2M_RESOURCE_CALLBACK(5, { avg_msg_size,NULL,NULL}),
		LWM2M_RESOURCE_CALLBACK(6, { NULL,NULL,start_reset}),
                );
LWM2M_INSTANCES(connectivity_statistics_instances,
		LWM2M_INSTANCE(0, connectivity_statistics_resources));
LWM2M_OBJECT(connectivity_statistics, 7, connectivity_statistics_instances);
/*---------------------------------------------------------------------------*/
void
ipso_connectivity_statistics_init(void)
{

 
  lwm2m_engine_register_object(&connectivity_statistics);
}
/*---------------------------------------------------------------------------*/
/** @} */
