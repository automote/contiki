/*
 * Copyright (c) 2013, Institute for Pervasive Computing, ETH Zurich
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
 * This file is part of the Contiki operating system.
 */

/**
 * \file
 *      Example resource
 * \author
 *      Matthias Kovatsch <kovatsch@inf.ethz.ch>
 */

#include "contiki.h"

#if PLATFORM_HAS_LEDS

#include <string.h>
#include "rest-engine.h"
#include "dev/leds.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINT6ADDR(addr) PRINTF("[%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x]", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF("[%02x:%02x:%02x:%02x:%02x:%02x]", (lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3], (lladdr)->addr[4], (lladdr)->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

#define LEDS_GREEN                    1
#define LEDS_YELLOW                   2
#define LEDS_RED                      4
#define LEDS_ALL                      7

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_put_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

/*A simple actuator example, depending on the color query parameter and post variable mode, corresponding led is activated or deactivated*/
RESOURCE(res_leds,
         "title=\"LEDs: ?color=r|g|b, PUT mode=on|off\";rt=\"Control\"",
         res_get_handler,
         NULL,
         res_put_handler,
         NULL);


static void
res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{

    /*char const * const leds = leds_get();
    unsigned char length = sizeof(leds);
    memcpy(buffer, leds, length);
    REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
    REST.set_header_etag(response, (uint8_t *) &length, 1);
    REST.set_response_payload(response, buffer, length);  
    printf(" LED =%u\n", leds);
    PRINTF(" LED =%u\n", leds);
    */

if (leds_get()==4)
{
    char const * const message = "RED LED ON";
     int length = 10;
     memcpy(buffer, message, length);
        REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
        REST.set_header_etag(response, (uint8_t *) &length, 1);
        REST.set_response_payload(response, buffer, length);  
    printf("RED LED ON\n", leds_get());
    PRINTF("RED LED ON\n", leds_get());
}

else if (leds_get()==1)
{   
    char const * const message = "GREEN LED ON";
     int length = 13;
     memcpy(buffer, message, length);
        REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
        REST.set_header_etag(response, (uint8_t *) &length, 1);
        REST.set_response_payload(response, buffer, length);  
    printf("GREEN LED ON\n", leds_get());
    PRINTF("GREEN LED ON\n", leds_get());
}

else if (leds_get()==2)
{
            char const * const message = "BLUE LED ON";
            int length = 10;
            memcpy(buffer, message, length);
            REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
            REST.set_header_etag(response, (uint8_t *) &length, 1);
            REST.set_response_payload(response, buffer, length);  
            printf("BLUE LED ON\n", leds_get());
            PRINTF("BLUE LED ON\n", leds_get());
}

else if (leds_get()==5)
{
            char const * const message = "R&G LED ON";
            int length = 10;
            memcpy(buffer, message, length);
            REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
            REST.set_header_etag(response, (uint8_t *) &length, 1);
            REST.set_response_payload(response, buffer, length);  
            printf("R&G LED ON\n", leds_get());
            PRINTF("R&G LED ON\n", leds_get());
}

else if (leds_get()==3)
 {
            char const * const message = "G&B LED ON";
            int length = 10;
            memcpy(buffer, message, length);
            REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
            REST.set_header_etag(response, (uint8_t *) &length, 1);
            REST.set_response_payload(response, buffer, length);  
            printf("B&G LED ON\n", leds_get());
            PRINTF("B&G LED ON\n", leds_get());
}

else if (leds_get()==6)
 {
            char const * const message = "R&B LED ON";
            int length = 10;
            memcpy(buffer, message, length);
            REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
            REST.set_header_etag(response, (uint8_t *) &length, 1);
            REST.set_response_payload(response, buffer, length);  
            printf("R&B LED ON\n", leds_get());
            PRINTF("R&B LED ON\n", leds_get());
}

else if (leds_get()==7)
 {
            char const * const message = "R&G&B LED ON";
            int length = 12;
            memcpy(buffer, message, length);
            REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
            REST.set_header_etag(response, (uint8_t *) &length, 1);
            REST.set_response_payload(response, buffer, length);  
            printf("R&G&B LED ON\n", leds_get());
            PRINTF("R&G&B LED ON\n", leds_get());
}

else 
{
     char const * const message = "LED OFF";
     int length = 7;
     memcpy(buffer, message, length);
        REST.set_header_content_type(response, REST.type.TEXT_PLAIN); 
        REST.set_header_etag(response, (uint8_t *) &length, 1);
        REST.set_response_payload(response, buffer, length); 
        printf("status OFF\n", leds_get());
        PRINTF("status OFF\n", leds_get());  
}
}

static void
res_put_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  size_t len = 0;
  const char *color = NULL;
  const char *mode = NULL;
  uint8_t led = 0;
  int success = 1;

  if((len = REST.get_query_variable(request, "color", &color))) {
    PRINTF("color %.*s\n", len, color);

    if(strncmp(color, "r", len) == 0) {
      led = LEDS_RED;
    } else if(strncmp(color, "g", len) == 0) {
      led = LEDS_GREEN;
    } else if(strncmp(color, "b", len) == 0) {
      led = LEDS_BLUE;
    } else {
      success = 0;
    }
  } else {
    success = 0;
} 
  
    if(success && (len = REST.get_post_variable(request, "mode", &mode))) {
    PRINTF("mode %s\n", mode);

    if(strncmp(mode, "on", len) == 0) {
      leds_on(led);
      
      if (leds_get()==4)
            {
                 printf("RED_LED status ON\n");
                 PRINTF("RED_LED status ON\n");
            }
        else if (leds_get()==1)
            {
                 printf("GREEN_LED status ON\n");
                 PRINTF("GREEN_LED status ON\n");
            }
       else if (leds_get()==2)
            {
                 printf("BLUE_LED status ON\n");
                 PRINTF("BLUE_LED status ON\n");
            }
        else if (leds_get()==3)
            {
                 printf("G&B_LED status ON\n");
                 PRINTF("G&B_LED status ON\n");
            }
        else if (leds_get()==6)
            {
                 printf("B&R_LED status ON\n");
                 PRINTF("B&R_LED status ON\n");
            }
        else if (leds_get()==5)
            {
                 printf("G&R_LED status ON\n");
                 PRINTF("G&R_LED status ON\n");
            }
        else if (leds_get()==7)
            {
                 printf("R&G&B_LED status ON\n");
                 PRINTF("R&G&B_LED status ON\n");
            }
        }
        
      else if(strncmp(mode, "off", len) == 0) {
      leds_off(led);
      //printf("LEDs status OFF\n");
      //PRINTF("LEDs status OFF\n");
    } else {
      success = 0;
    }
  } else {
    success = 0;
  } if(!success) {
    REST.set_response_status(response, REST.status.BAD_REQUEST);
  }
}
#endif /* PLATFORM_HAS_LEDS */