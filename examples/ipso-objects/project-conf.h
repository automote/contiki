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

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#ifdef BOARD_STRING
#define LWM2M_DEVICE_MODEL_NUMBER BOARD_STRING
#elif defined(CONTIKI_TARGET_WISMOTE)
#include "dev/watchdog.h"
#define LWM2M_DEVICE_MODEL_NUMBER "wismote"
#define LWM2M_DEVICE_MANUFACTURER "Arago Systems"
#define LWM2M_DEVICE_SERIAL_NO    "001"
#define PLATFORM_REBOOT watchdog_reboot
#endif



#define IPSO_TEMPERATURE example_ipso_temperature
#define IPSO_ILLUMINANCE example_ipso_illuminance
#define IPSO_3202 	 example_ipso_analog_input

/******************	by thing tronics ****************************/
#define IPSO_3201 	 example-ipso-ldr-input 	 
#define IPSO_LIGHT_CONTROL example_ipso_light_control
#define IPSO_RELAY_CONTROL example_ipso_relay_control
/****************************************************************/
/*======================================================*/
//#ifndef PROJECT_CONF_H_
//#define PROJECT_CONF_H_

/*#undef  NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO         cc1200_driver
#define NETSTACK_CONF_RDC           nullrdc_driver
#define CC1200_CONF_USE_GPIO2       0
#define CC1200_CONF_USE_RX_WATCHDOG 0
#define ANTENNA_SW_SELECT_DEF_CONF  ANTENNA_SW_SELECT_SUBGHZ
*/
//#endif /* PROJECT_CONF_H_ */


/*================================================*/
/*#undef  NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO                                 cc1200_driver
#define CC1200_CONF_RF_CFG                 cc1200_802154g_863_870_fsk_50kbps
#define ANTENNA_SW_SELECT_DEF_CONF              ANTENNA_SW_SELECT_SUBGHZ
#define CC1200_CONF_USE_GPIO2                               0
#define CC1200_CONF_USE_RX_WATCHDOG                         0

#define NULLRDC_CONF_ACK_WAIT_TIME                          (RTIMER_SECOND / 200)
#define NULLRDC_CONF_AFTER_ACK_DETECTED_WAIT_TIME      (RTIMER_SECOND / 1500)
#define NULLRDC_CONF_802154_AUTOACK                         1
#define NULLRDC_CONF_802154_AUTOACK_HW                      1
#define NULLRDC_CONF_SEND_802154_ACK                        0
#define CONTIKIMAC_CONF_CCA_CHECK_TIME              (RTIMER_ARCH_SECOND / 800)
#define CONTIKIMAC_CONF_CCA_SLEEP_TIME                (RTIMER_ARCH_SECOND / 120)
#define CONTIKIMAC_CONF_LISTEN_TIME_AFTER_PACKET_DETECTED  (RTIMER_ARCH_SECOND / 8)
#define CONTIKIMAC_CONF_AFTER_ACK_DETECTED_WAIT_TIME    (RTIMER_SECOND / 300)
#define CONTIKIMAC_CONF_INTER_PACKET_INTERVAL               (RTIMER_SECOND / 200)

*/



/* Change to match your configuration */
#define IEEE802154_CONF_PANID            0XABCE
#define RF_CORE_CONF_CHANNEL                 25

/**
 * Disabling RDC and CSMA to save memory on constrained devices.
 */
#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC              nullrdc_driver

#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC              nullmac_driver

/* Disabling TCP on CoAP nodes. */
#undef UIP_CONF_TCP
#define UIP_CONF_TCP                   0

/* Increase rpl-border-router IP-buffer when using more than 64. */
#undef REST_MAX_CHUNK_SIZE
//#define REST_MAX_CHUNK_SIZE            64
#define REST_MAX_CHUNK_SIZE            256

/* Multiplies with chunk size, be aware of memory constraints. */
#undef COAP_MAX_OPEN_TRANSACTIONS
#define COAP_MAX_OPEN_TRANSACTIONS     4

/* Filtering .well-known/core per query can be disabled to save space. */
#undef COAP_LINK_FORMAT_FILTERING
#define COAP_LINK_FORMAT_FILTERING     0
#undef COAP_PROXY_OPTION_PROCESSING
#define COAP_PROXY_OPTION_PROCESSING   0

/* Enable client-side support for COAP observe */
#define COAP_OBSERVE_CLIENT 1

#endif /* PROJECT_CONF_H_ */
