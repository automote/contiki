CONTIKI_PROJECT = example-ipso-objects

#CONTIKI_SOURCEFILES += serial-protocol.c example-ipso-ldr-input.c

CONTIKI_SOURCEFILES += serial-protocol.c example-ipso-illuminance.c example-ipso-ldr-input.c example-ipso-temperature1.c example-ipso-relay.c 
CONTIKI_SOURCEFILES += example-ipso-light-control.c
#CONTIKI_SOURCEFILES += adc-sensors.c relay.c

all: $(CONTIKI_PROJECT)

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

APPS += rest-engine
APPS += er-coap
APPS += oma-lwm2m
APPS += ipso-objects


CONTIKI=../..
CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include

# border router rules
$(CONTIKI)/tools/tunslip6:	$(CONTIKI)/tools/tunslip6.c
	(cd $(CONTIKI)/tools && $(MAKE) tunslip6)

connect-router:	$(CONTIKI)/tools/tunslip6
	sudo $(CONTIKI)/tools/tunslip6 aaaa::1/64

connect-router-cooja:	$(CONTIKI)/tools/tunslip6
	sudo $(CONTIKI)/tools/tunslip6 -a 127.0.0.1 -p 60001 aaaa::1/64

connect-router-native:	$(CONTIKI)/examples/ipv6/native-border-router/border-router.native
	sudo $(CONTIKI)/exmples/ipv6/native-border-router/border-router.native -a 127.0.0.1 -p 60001 aaaa::1/64
