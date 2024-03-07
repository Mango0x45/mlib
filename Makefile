MAKEFLAGS = -j8
srcs := $(shell find . -name '*.c')
objs := $(srcs:.c=.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CC = gcc
CFLAGS = -std=c23 -Iinclude
endif
ifeq ($(UNAME_S),Darwin)
CC = gcc-13
CFLAGS = -std=c2x -Iinclude
endif

all: $(objs)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(objs)

.PHONY: clean
