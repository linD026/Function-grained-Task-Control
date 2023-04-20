VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
PWD := $(CURDIR)

INC=$(PWD)/include
INC_PARAMS=$(INC:%=-I%)

CC ?= gcc
CFLAGS:=-g 
CFLAGS+=-Wall
CFLAGS+=-O1
CFLAGS+=-pthread
CFLAGS+=-fPIC
CFLAGS+=-std=c11

CFLAGS+=-D'CONFIG_VERSION=$(VERSION)'
CFLAGS+=-D'CONFIG_PATCHLEVEL=$(PATCHLEVEL)'
CFLAGS+=-D'CONFIG_SUBLEVEL=$(SUBLEVEL)'

DEBUG_FLAGS=

ifneq ($(strip $(debug)),)
DEBUG_FLAGS+=-fsanitize=thread
DEBUG_FLAGS+=-D'CONFIG_DEBUG'
CFLAGS+=$(DEBUG_FLAGS)
endif

SRC:=src/init.c
SRC+=src/transfer.c
SRC+=src/worker.c
SRC+=src/lightweight_system.c

OBJ:=$(SRC:.c=.o)

BIN=ftc
BUILD_DIR=func-task-control

ifeq ($(quiet),1)
FTC_CC=@$(CC)
FTC_LD=@$(LD)
FTC_LD_GEN=@$(LD_GEN)
FTC_RM=@rm
FTC_MKDIR=@mkdir
FTC_CP=@cp
FTC_MV=@mv
FTC_BASH=@bash
else
FTC_CC=$(CC)
FTC_LD=$(LD)
FTC_LD_GEN=$(LD_GEN)
FTC_RM=rm
FTC_MKDIR=mkdir
FTC_CP=cp
FTC_MV=mv
FTC_BASH=bash
endif

LIB=lib/libmthpc.so

%.o: %.c
	$(FTC_CC) $(CFLAGS) $(INC_PARAMS) -c $< -o $@

$(BIN): $(OBJ)
	$(FTC_CC) $(CFLAGS) $(INC_PARAMS) $(OBJ) $(LIB) -o $@

clean:
	$(FTC_RM) -f src/*.o
	$(FTC_RM) -f $(BIN)

cleanall: clean
	$(FTC_RM) -rf $(BUILD_DIR)

cscope:
	find $(PWD) -name "*.c" -o -name "*.h" > $(PWD)/cscope.files
	cscope -b -q

indent:
	clang-format -i include/*/*.[ch]
	clang-format -i src/*.[ch]

ifeq ($(quiet), 1)
.SILENT:
endif


