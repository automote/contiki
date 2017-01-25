/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef PROJECT_ROUTER_CONF_H_
#define PROJECT_ROUTER_CONF_H_

#ifndef WITH_NON_STORING
#define WITH_NON_STORING 0 /* Set this to run with non-storing mode */
#endif /* WITH_NON_STORING */

#if WITH_NON_STORING
#undef RPL_NS_CONF_LINK_NUM
#define RPL_NS_CONF_LINK_NUM 40 /* Number of links maintained at the root */
#undef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES 0 /* No need for routes */
#undef RPL_CONF_MOP
#define RPL_CONF_MOP RPL_MOP_NON_STORING /* Mode of operation*/
#endif /* WITH_NON_STORING */

#define IEEE802154_CONF_PANID            0XABCE
#ifndef UIP_FALLBACK_INTERFACE
#define UIP_FALLBACK_INTERFACE rpl_interface
#endif

#ifndef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM          4
#endif
//#define IEEE802154_CONF_PANID            0x1234

/*#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    140
#endif

#ifndef UIP_CONF_RECEIVE_WINDOW
#define UIP_CONF_RECEIVE_WINDOW  60
#endif*/

#ifndef WEBSERVER_CONF_CFS_CONNS
#define WEBSERVER_CONF_CFS_CONNS 2
#endif

#endif /* PROJECT_ROUTER_CONF_H_ */


/*==========================================*/
/*#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#undef  NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO         cc1200_driver
#define NETSTACK_CONF_RDC           nullrdc_driver
#define CC1200_CONF_USE_GPIO2       0
#define CC1200_CONF_USE_RX_WATCHDOG 0
#define ANTENNA_SW_SELECT_DEF_CONF  ANTENNA_SW_SELECT_SUBGHZ

#endif*/ /* PROJECT_CONF_H_ */
/*==================================*/
#undef  NETSTACK_CONF_RADIO
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


