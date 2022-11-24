PROGRAM=minestorm
LIBS_PATH=libs/

CC=gcc
CFLAGS=-Ofast 
CPPFLAGS= -Iinclude/ -Iinclude/libs/
LDFLAGS=-L$(LIBS_PATH)x86_64-linux-gnu -L$(LIBS_PATH)
LDLIBS=-lglfw3 -lcanvas -lstdc++ -ldl -lpthread -lm

CSRC = $(wildcard src/*.c) $(wildcard src/game/*.c)
OBJS = $(CSRC:.c=.o)

DEPS=$(OBJS:.o=.d)

.PHONY: all

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM).exe config.bin
