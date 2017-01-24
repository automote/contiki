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
power_switch_control_instances *
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
 *         Implementation of OMA LWM2M / IPSO Power Control For PSoC [FAN1, FAN2, Socket1]
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 *    	   Amit Sharma <amit.sh1094@gmail.com>
 */

#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
// PSoC Header file
#ifdef PSOC
#include "dev/psoc.h"
#endif
extern tx_Data;
extern rx_Data;
/*---------------------------------------------------------------------------*/
// #define
#ifndef MAX_3306_PSOC_RESOURCE
	#define MAX_3306_PSOC_RESOURCE 2
#endif

/*----------------------------------------------------------------------------*/
extern const struct ipso_objects_actuator IPSO_LIGHT_CONTROL[MAX_3306_PSOC_RESOURCE];
/*---------------------------------------------------------------------------*/
// Global Variable Definition
struct psoc_state {
	unsigned long last_on_time;
	uint32_t total_on_time;
	int dim_level;
	uint8_t is_on;
};

static struct ctimer periodic_timer;
//static struct psoc_state states[MAX_3306_PSOC_RESOURCE];
static lwm2m_instance_t power_switch_control_instances[MAX_3306_PSOC_RESOURCE];
/*---------------------------------------------------------------------------*/
static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
	uint8_t status;
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	uint8_t idx = ctx->object_instance_index;
		printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}
	tx_Data++;
	rx_Data++;
	switch(idx)
	{
	case 0: status=IPSO_LIGHT_CONTROL[0].is_on_0();
		break;
	case 1: status=IPSO_LIGHT_CONTROL[0].is_on_1();
		break;
	case 3: status=IPSO_LIGHT_CONTROL[0].is_on_2();	
		break;
	case 4: status=IPSO_LIGHT_CONTROL[0].is_on_5();
		break;
	case 5: status=IPSO_LIGHT_CONTROL[0].is_on_6();
		break;
	case 7: status=IPSO_LIGHT_CONTROL[0].is_on_7();
		break;
	case 8: status=IPSO_LIGHT_CONTROL[idx].is_on_8();
		break;
	case 9: status=IPSO_LIGHT_CONTROL[idx].is_on_9();
		break;
	case 10: status=IPSO_LIGHT_CONTROL[idx].is_on_10();
		break;
	default : printf("Cross maximum number of instances...%d\n",idx);
			break;
	
	
	}


	printf("Func[%s] @ Line No[%d] id[%d] with state[%d]\n", __func__, __LINE__, idx, status);
	//return ctx->writer->write_boolean(ctx, outbuf, outsize, states[idx].is_on ? 1 : 0);
	return ctx->writer->write_boolean(ctx, outbuf, outsize, status);
}
/*---------------------------------------------------------------------------*/
static int
write_state(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
	int status;
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	int value;
	size_t len;

	uint8_t idx = ctx->object_instance_index;
	printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}
	printf("Func[%s] @ Line No[%d] id[%d] \n", __func__, __LINE__, idx);
	len = ctx->reader->read_boolean(ctx, inbuf, insize, &value);
	tx_Data;
	switch(idx)
        {
        case 0: status=IPSO_LIGHT_CONTROL[0].is_on_0();
                break;
        case 1: status=IPSO_LIGHT_CONTROL[0].is_on_1();
                break;
    /*    case 2: status=IPSO_LIGHT_CONTROL[idx].is_on_2();
                break;
        case 5: status=IPSO_LIGHT_CONTROL[idx].is_on_5();
                break;
        case 6: status=IPSO_LIGHT_CONTROL[idx].is_on_6();
                break;
        case 7: status=IPSO_LIGHT_CONTROL[idx].is_on_7();
                break;
        case 8: status=IPSO_LIGHT_CONTROL[idx].is_on_8();
                break;
        case 9: status=IPSO_LIGHT_CONTROL[idx].is_on_9();
                break;
        case 10: status=IPSO_LIGHT_CONTROL[idx].is_on_10();
                break;
        default : printf("Cross maximum number of instances...%d\n",idx);
                        break;*/


        }
	if(len > 0) 
	{
		if(value) 
		{
			if(!status)
			//if(!states[idx].is_on) 
			{
				printf("Func[%s] @ Line No[%d] :: on flag set as true and dim level as 100\n", __func__, __LINE__);
				switch(idx)
					{
						case 0 :IPSO_LIGHT_CONTROL[0].set_on_0(1);
							break;
						case 1: IPSO_LIGHT_CONTROL[0].set_on_1(1);
							break;
				/*		case 2: IPSO_LIGHT_CONTROL[idx].set_on_2(1);
							break;
						case 5: IPSO_LIGHT_CONTROL[idx].set_on_5(1);
							break;
						case 6: IPSO_LIGHT_CONTROL[idx].set_on_6(1);
							break;
						case 7: IPSO_LIGHT_CONTROL[idx].set_on_7(1);
							break;
						case 8: IPSO_LIGHT_CONTROL[idx].set_on_8(1);
							break;
						case 9: IPSO_LIGHT_CONTROL[idx].set_on_9(1);
							break;
						case 10: IPSO_LIGHT_CONTROL[idx].set_on_10(1);
							break;*/
						default : printf("Error max number of insatnce cross..\n");
							break;
					}
				
				//states[idx].is_on = 1;
				//states[idx].last_on_time = clock_seconds();
				//states[idx].dim_level = 100;
//#ifdef PSOC
//				psoc.configure(RESOURCE_SWITCH1 + idx, 100);
//#endif
//				printf("Calling configure API from psoc.c, so that resource[SOCKET%d] be On i.e. value set as 100 \n", idx);
			}
		} 
		else 
		{
			if(status) 
			{
				printf("Func[%s] @ Line No[%d] :: on flag set as flase and dim level as 0\n", __func__, __LINE__);
			switch(idx)
                                        {
                                                case 0 :IPSO_LIGHT_CONTROL[0].set_on_0(0);
                                                        break;
                                                case 1: IPSO_LIGHT_CONTROL[0].set_on_1(0);
                                                        break;
                                               /* case 2: IPSO_LIGHT_CONTROL[idx].set_on_2(0);
                                                        break;
                                                case 5: IPSO_LIGHT_CONTROL[idx].set_on_5(0);
                                                        break;
                                                case 6: IPSO_LIGHT_CONTROL[idx].set_on_6(0);
                                                        break;
                                                case 7: IPSO_LIGHT_CONTROL[idx].set_on_7(0);
                                                        break;
                                                case 8: IPSO_LIGHT_CONTROL[idx].set_on_8(0);
                                                        break;

                                                case 9: IPSO_LIGHT_CONTROL[idx].set_on_9(0);
                                                        break;
                                                case 10: IPSO_LIGHT_CONTROL[idx].set_on_10(0);
                                                        break;

                                                */default : printf("Error max number of insatnce cross..\n");
                                                        break;
                                        }

			//	states[idx].is_on = 0;
			//	states[idx].last_on_time = clock_seconds();
			//	states[idx].dim_level = 0;
			//	states[idx].total_on_time += clock_seconds() - states[idx].last_on_time;
//#ifdef PSOC
//				psoc.configure(RESOURCE_SWITCH1 + idx, 0);
//#endif
//				printf("Calling configure API from psoc.c, so that resource[SOCKET%d] be On i.e. value set as 0 \n", idx);
			}
		}
	}
	printf("Func[%s] @ Line No[%d] Exit\n", __func__, __LINE__);
	return len;
}
/*---------------------------------------------------------------------------*/
static int
read_dim(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
	int dim_level;
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	uint8_t idx = ctx->object_instance_index;
	printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}
//	else if(idx == 2)
//	{
//		printf("Func[%s] @ Line No[%d] dim not possible for Socket Resource\n", __func__, __LINE__);
//		return 0;
//	}
	switch (idx)
	{
	case 0: dim_level=IPSO_LIGHT_CONTROL[0].get_dim_level_0();
		break;
	case 1: dim_level=IPSO_LIGHT_CONTROL[0].get_dim_level_1();
		break;
/*	case 2: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_2();
		break;
	case 5: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_4();
		break;
	case 6: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_6();
		break;
	case 7: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_7();
		break;
	case 8: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_8();
		break;
	case 9: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_9();
		break;
	case 10: dim_level=IPSO_LIGHT_CONTROL[idx].get_dim_level_10();
		break;
*/	}
	printf("Func[%s] @ Line No[%d] id[%d] with dim_level[%d]\n", __func__, __LINE__, idx,dim_level);
	//return ctx->writer->write_int(ctx, outbuf, outsize, states[idx].dim_level);
	return ctx->writer->write_int(ctx, outbuf, outsize,dim_level);
}
/*---------------------------------------------------------------------------*/
static int
write_dim(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
          uint8_t *outbuf, size_t outsize)
{
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	int32_t value;
	size_t len;

	uint8_t idx = ctx->object_instance_index;
	printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}
	//else if(idx == 2)
//	{
//		printf("Func[%s] @ Line No[%d] dim not possible for Socket Resource\n", __func__, __LINE__);
//		return 0;
//	}

	len = ctx->reader->read_int(ctx, inbuf, insize, &value);
	if(len > 0) 
	{
		if(value < 0) 
		{
			value = 0;
		} 
		else if(value > 100) 
		{
			value = 100;
		}

//		states[idx].dim_level = value;
		switch(idx)
		{
		case 0:  IPSO_LIGHT_CONTROL[0].set_dim_level_0(value);
		       	break;
		case 1:  IPSO_LIGHT_CONTROL[0].set_dim_level_1(value);
		       	break;
	/*	case 2:  IPSO_LIGHT_CONTROL[idx].set_dim_level_2(value);
		       	break;
		case 5:  IPSO_LIGHT_CONTROL[idx].set_dim_level_5(value);
		       	break;
		case 6:  IPSO_LIGHT_CONTROL[idx].set_dim_level_6(value);
		       	break;
		case 7:  IPSO_LIGHT_CONTROL[idx].set_dim_level_7(value);
		       	break;
		case 8:  IPSO_LIGHT_CONTROL[idx].set_dim_level_8(value);
		       	break;
		case 9:  IPSO_LIGHT_CONTROL[idx].set_dim_level_9(value);
		       	break;
		case 10:  IPSO_LIGHT_CONTROL[idx].set_dim_level_10(value);
		       	break;
*/



		}
//#ifdef PSOC
//		psoc.configure(RESOURCE_SWITCH1 + idx, value);
//#endif
//		printf("Calling configure API from psoc.c, so that resource[SOCKET%d] be On i.e. value set as %d \n", idx), value;
//		if(value > 0) 
//		{
//			if(!states[idx].is_on) 
//			{
//				states[idx].is_on = 1;
//				states[idx].last_on_time = clock_seconds();
//			}
//		} 
//		else 
//		{
//			if(states[idx].is_on) 
//			{
//				states[idx].total_on_time += clock_seconds() - states[idx].last_on_time;
//				states[idx].is_on = 0;
//			}
//		}
	}
	printf("Need to call configure API from psoc.c, so that resource[%d] value set according to dim level.", idx);
	printf("Func[%s] @ Line No[%d] Exit\n", __func__, __LINE__);
	return len;
}
/*---------------------------------------------------------------------------*/
/*static int
read_on_time(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	unsigned long now;
	uint8_t idx = ctx->object_instance_index;
printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}
	if(states[idx].is_on) 
	{*/
		/* Update the on time */
	/*	now = clock_seconds();
		states[idx].total_on_time += now - states[idx].last_on_time;
		states[idx].last_on_time = now;
	}
	printf("Func[%s] @ Line No[%d] :: resource id[%d]Exit\n", __func__, __LINE__, idx);
	return ctx->writer->write_int(ctx, outbuf, outsize, (int32_t)states[idx].total_on_time);
}*/
/*---------------------------------------------------------------------------*/
/*static int
write_on_time(lwm2m_context_t *ctx,
		const uint8_t *inbuf, size_t insize,
		uint8_t *outbuf, size_t outsize)
{
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	int32_t value;
	size_t len;

	uint8_t idx = ctx->object_instance_index;
printf("ctx->object_instance_index---->%d\n",idx);
	if(idx >= MAX_3306_PSOC_RESOURCE) 
	{
		printf("Func[%s] @ Line No[%d] Invalid Resource Type\n", __func__, __LINE__);
		return 0;
	}

	len = ctx->reader->read_int(ctx, inbuf, insize, &value);
	if(len > 0 && value == 0) 
	{
		states[idx].total_on_time = 0;
		if(states[idx].is_on) 
		{
			states[idx].last_on_time = clock_seconds();
		}
	}
	printf("Func[%s] @ Line No[%d] :: id[%d] Exit\n", __func__, __LINE__, idx);
	return len;
}*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(power_switch_psoc_resources,
		LWM2M_RESOURCE_CALLBACK(5850, { read_state, write_state, NULL }),
		LWM2M_RESOURCE_CALLBACK(5851, { read_dim, write_dim, NULL }),
//		LWM2M_RESOURCE_CALLBACK(5852, { read_on_time, write_on_time, NULL }),
                );

LWM2M_OBJECT(power_switch_control, 3306, power_switch_control_instances);
/*---------------------------------------------------------------------------*/
/*static void
handle_periodic_timer(void *ptr)
{
	int last_value_0,last_value_1;
	int dim_level_0,dim_level_1;
//	Only notify when the value has changed since last 
		if((dim_level_0=IPSO_LIGHT_CONTROL[0].get_dim_level_0()) && last_value_0 != dim_level_0){
			//  if(read_ldr_input(&v) && v != last_value) {
			last_value_0=dim_level_0;
			lwm2m_object_notify_observers(&power_switch_control, "/0/5851");
		}


		if((dim_level_1=IPSO_LIGHT_CONTROL[0].get_dim_level_1()) && last_value_1 != dim_level_1)
		{
			last_value_1=dim_level_1;

			lwm2m_object_notify_observers(&power_switch_control, "/1/5851");
		}
		ctimer_reset(&periodic_timer);
}
*/

void ipso_actuation_switch_control_init(void)
{
	printf("Func[%s] @ Line No[%d] Enter\n", __func__, __LINE__);
	lwm2m_instance_t template = LWM2M_INSTANCE(0, power_switch_psoc_resources);
	int loop;
	for(loop = 0; loop < MAX_3306_PSOC_RESOURCE; loop++)
	{
		printf("Func[%s] @ Line No[%d] :: inside for loop[%d]\n", __func__, __LINE__, loop);
		power_switch_control_instances[loop] = template;
		power_switch_control_instances[loop].id = loop;
	//	states[loop].last_on_time = clock_seconds();
	}
#if 0
#ifdef IPSO_LIGHT_CONTROL
	if(IPSO_LIGHT_CONTROL.init) {
		IPSO_LIGHT_CONTROL.init();
	}
	if(IPSO_LIGHT_CONTROL.is_on) {
		is_on = IPSO_LIGHT_CONTROL.is_on();
	}
	if(IPSO_LIGHT_CONTROL.get_dim_level) {
		dim_level = IPSO_LIGHT_CONTROL.get_dim_level();
		if(dim_level > 0 && IPSO_LIGHT_CONTROL.is_on == NULL) {
			is_on = 1;
		}
	}
#endif /* IPSO_LIGHT_CONTROL */
#endif
//	ctimer_set(&periodic_timer, CLOCK_SECOND * 10, handle_periodic_timer, NULL);


	lwm2m_engine_register_object(&power_switch_control);
	printf("Func[%s] @ Line No[%d] :: Exit\n", __func__, __LINE__);
}
/*---------------------------------------------------------------------------*/
/** @} */
