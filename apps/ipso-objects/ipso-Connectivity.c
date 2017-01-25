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
 *         Amar Garg <amar.garg@thingtronics.com>
 */

#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include <string.h>
#include "rpl.h"

uip_ipaddr_t *addr;
char ip_address[45];

/*---------------------------------------------------------------------------*/
/*static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  return ctx->writer->write_boolean(ctx, outbuf, outsize, is_on ? 1 : 0);
}*/
/*---------------------------------------------------------------------------*/
/*static void
print_local_addresses(void)
{
	int i,f,len=0,len_1=0;
	uint8_t state;
	uint16_t a;
	uip_ipaddr_t *addr;
	char ip_address[30];
	char ip_Address[35];


	printf("Server IPv6 addresses:\n");
	for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
		state = uip_ds6_if.addr_list[i].state;
		if(uip_ds6_if.addr_list[i].isused &&
				(state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
			printf(" ");
			//uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
			//  printf("%s\n",(&uip_ds6_if.addr_list[i].ipaddr));
			addr=&uip_ds6_if.addr_list[i].ipaddr;
			for(i = 0, f = 0; i < sizeof(uip_ipaddr_t); i += 2) {
				a = (addr->u8[i] << 8) + addr->u8[i + 1];
		//		printf("%x  ",a);
				if(a == 0 && f >= 0) {
					if(f++ == 0) {
						printf("::");
					}
				} else
				{
					if(f > 0) {
						f = -1;
					} else if(i > 0) {
						printf(":");
					}
					printf("%x", a);
				}
			}
			printf("\n");
		for(i = 0, f = 0; i < sizeof(uip_ipaddr_t); i++) {
                                a = (addr->u8[i]) ;
					printf("%x ",a);
			// uint8_t b =a;
		        ip_address[len++] = (a >> 4) > 9 ? 'A' - 10 + (a >> 4) : '0' + (a >> 4);
       	         	ip_address[len++] = (a & 0xf) > 9 ? 'A' - 10 + (a & 0xf) : '0' + (a & 0xf);
						if((i+1)%2==0)
							ip_address[len++]=':';
					
			//	a = addr->u8[i + 1];
		//			printf("%x\n",a);
				// uint8_t b =linkaddr_node_addr.u8[i];
     			  // 	ip_address[len++] = (b >> 4) > 9 ? 'A' - 10 + (b >> 4) : '0' + (b >> 4);
        		//	ip_address[len++] = (b & 0xf) > 9 ? 'A' - 10 + (b & 0xf) : '0' + (b & 0xf);
		
			}
			ip_address[len]='\0';
					printf("%s\n",ip_address);
						printf("\n");
		}
	}

}*/
/*------------------------------------------------------------------------*/
static int 
read_network(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint8_t network=23;

	
	return ctx->writer->write_int(ctx, outbuf, outsize,network);


}
/*---------------------------------------------------------------------------*/
static int 
available_network(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint8_t available_network=23;
	//	available_network=23;


	return ctx->writer->write_int(ctx, outbuf, outsize,available_network);

}
/*---------------------------------------------------------------------------*/
static int
read_radio_strength(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	int16_t radio_strength;
        radio_strength = packetbuf_attr(PACKETBUF_ATTR_RSSI);
        printf("RSSI: %ddBm ", radio_strength);

	return ctx->writer->write_int(ctx, outbuf, outsize,radio_strength);

}
/*--------------------------------------------------------------------------*/
static int 
read_link_quality(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint8_t link_quality;
	printf("%d\n",outsize);
	link_quality = packetbuf_attr(PACKETBUF_ATTR_LINK_QUALITY);
	printf("LQI: %u\n", link_quality);


	return ctx->writer->write_int(ctx, outbuf, outsize,link_quality);
}
/*--------------------------------------------------------------------------*/
static int 
read_ip_address(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	int i,f,len=0;
	uint8_t state;
	uint16_t a;
	//char ip_address[45];
	printf("Server IPv6 addresses:\n");
	for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
		state = uip_ds6_if.addr_list[i].state;
		if(uip_ds6_if.addr_list[i].isused &&
				(state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
			printf(" ");
			addr=&uip_ds6_if.addr_list[i].ipaddr;
			for(i = 0, f = 0; i < sizeof(uip_ipaddr_t); i+=2) {
				a = (addr->u8[i] << 8) + addr->u8[i + 1];
				if(a == 0 && f >= 0) {
					if(f++ == 0) {
						printf("::");

					}
				} else
				{
					if(f > 0) {
						f = -1;
					} else if(i > 0) {

						printf(":");
					}


					printf("%x", a);


				}
			}
			printf("\n");
			for(i = 0; i < sizeof(uip_ipaddr_t); i++) {
				a = (addr->u8[i]) ;


				ip_address[len++] = (a >> 4) > 9 ? 'A' - 10 + (a >> 4) : '0' + (a >> 4);
				ip_address[len++] = (a & 0xf) > 9 ? 'A' - 10 + (a & 0xf) : '0' + (a & 0xf);
				if((i+1)%2==0)
					ip_address[len++]=':';




			}
			ip_address[len]='\0';

			printf("%s\n",ip_address);
			printf("\n");
		}
	}



	return ctx->writer->write_string(ctx,outbuf,outsize,ip_address,strlen(ip_address));
}
/*---------------------------------------------------------------------------*/
	static int
read_router_ip_address(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	char router_ip_address[45];

	int i,len=0;
	uint16_t a;

	rpl_dag_t *dag;
	uip_ipaddr_t *address;
	dag = rpl_get_dag(addr);
	address=rpl_get_parent_ipaddr(dag->preferred_parent);

	for(i=0;i<16;i=i+2)
	{

		a = (address->u8[i] << 8) + address->u8[i + 1];
		printf("%x\n",a);
	}
	for(i = 0; i < sizeof(uip_ipaddr_t); i++) {
		a = (address->u8[i]) ;
		router_ip_address[len++] = (a >> 4) > 9 ? 'A' - 10 + (a >> 4) : '0' + (a >> 4);
		router_ip_address[len++] = (a & 0xf) > 9 ? 'A' - 10 + (a & 0xf) : '0' + (a & 0xf);
		if((i+1)%2==0)
			router_ip_address[len++]=':';
	}
	router_ip_address[len]='\0';
	printf("parent ip is %s\n",router_ip_address);
//	if(!ip_address[0])                        //To ensure the ip address variable is filled with Data
//		read_ip_address(ctx,outbuf,outsize);   
	for(i=0;i<4;i++)                                 
		router_ip_address[i]=ip_address[i];             
	printf("After adding Prefix %s\n",router_ip_address);


	return ctx->writer->write_string(ctx, outbuf,outsize,router_ip_address,strlen(router_ip_address));
}
/*---------------------------------------------------------------------------*/
static int
read_link_utilization(lwm2m_context_t *ctx, uint8_t *outbuf ,size_t outsize)
{
	uint8_t link_utilization;




	return ctx->writer->write_int(ctx, outbuf, outsize,link_utilization);
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(connectivity_resources,
                LWM2M_RESOURCE_CALLBACK(0, { read_network, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(1, { available_network, NULL, NULL }),
                LWM2M_RESOURCE_CALLBACK(2, { read_radio_strength, NULL, NULL }),
		LWM2M_RESOURCE_CALLBACK(3, { read_link_quality,NULL,NULL}),
		LWM2M_RESOURCE_CALLBACK(4, { read_ip_address,NULL,NULL}),
		LWM2M_RESOURCE_CALLBACK(5, { read_router_ip_address,NULL,NULL }),
		LWM2M_RESOURCE_CALLBACK(6, { read_link_utilization,NULL ,NULL}),
                );
LWM2M_INSTANCES(connectivity_instances,
		LWM2M_INSTANCE(0, connectivity_resources));
LWM2M_OBJECT(connectivity, 4, connectivity_instances);
/*---------------------------------------------------------------------------*/
void
ipso_connectivity_init(void)
{

 
  lwm2m_engine_register_object(&connectivity);
}
/*---------------------------------------------------------------------------*/
/** @} */
