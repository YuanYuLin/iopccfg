
TARGET = iopccfg.elf

CFLAGS += -I$(SDKSTAGE)/usr/include/iopccfg
CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 

CFLAGS += -I/home/yyl/data/boards/build_system/libiopccfg -I/usr/include/json-c
LDFLAGS += -L/home/yyl/data/boards/build_system/libiopccfg -L/usr/lib/x86_64-linux-gnu/
LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 
LDFLAGS += -ljson-c
LDFLAGS += -liopccfg

INCLUDES += 

SRC = 
SRC += main.c

include Makefile.include
