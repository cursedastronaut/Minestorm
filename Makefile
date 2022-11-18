PROGRAM=minestorm
LIBS_PATH=libs/

CC=x86_64-w64-mingw32-gcc
CFLAGS=-Ofast 
CPPFLAGS= -Iinclude/ -Iinclude/libs/
LDFLAGS=-L$(LIBS_PATH)x86_64-w64-mingw32 -L$(LIBS_PATH)
LDLIBS=-lglfw3 -lcanvas -lstdc++ -lgdi32

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
