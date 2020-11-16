# Makefile for the project

TARGET = fifo_test

CUR_DIR := .
TOP_DIR := $(CUR_DIR)/..

CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar cr
STRIP = $(CROSS_COMPILE)strip

# -Werror
CFLAGS = -O2 -Wall -Wno-unused-function
LDFLAG += -Wl,-gc-sections
LIBS = -lpthread -lrt -lm

EFLAGS := -DOS_LINUX
EFLAGS += -I$(TOP_DIR)/include
EFLAGS += -I$(TOP_DIR)/util/
EFLAGS += -I$(TOP_DIR)/util/ds
EFLAGS += -I$(TOP_DIR)/platform/thread

SRCDIRS  := .
SRCDIRS += $(TOP_DIR)/util
SRCDIRS += $(TOP_DIR)/platform/thread
SRCFIXS  := .c

#SRCDIRS  += $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}')

SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCFIXS))))
SRCS += $(TOP_DIR)/util/ds/fifo.c
OBJS := $(patsubst %.c,%.o,$(SRCS))

# for debug
$(warning source list $(SRCS))
# $(warning objs list $(OBJS))


CFLAGS += $(EFLAGS)


$(TARGET): $(OBJS)
	$(CC) $(LDFLAG) -o $@ $^ $(LIBS)
	$(STRIP) $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS) *.a *~

