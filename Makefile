MAKEFLAGS = -j8
srcs := $(shell find . -name '*.c')
objs := $(srcs:.c=.o)

all: $(objs)
%.o: %.c
	gcc-13 -std=c2x -Iinclude -c -o $@ $<

clean:
	rm -f $(objs)

.PHONY: clean
