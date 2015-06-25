
TARGET = iopccfg.elf

CFLAGS += -I$(SDKSTAGE)/usr/include/iopccfg
CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += -I$(SDKSTAGE)/usr/include/json-c

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 
LDFLAGS += -ljson-c
LDFLAGS += -liopccfg

SRC = 
SRC += main.c

include Makefile.include
