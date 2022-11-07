CFLAGS=-Iinclude -Llibs/x86_64-linux-gnu -lglfw3 -lcanvas -lstdc++ -ldl -lm -lpthread
CPPFLAGS=-MMD
LDFLAGS=
LDLIBS=
 
OBJS=src/app.c src/main.c src/squareception.c
DEPS=$(OBJS:.o=.d)
 
.PHONY: all clean
 
all: squareception
 
-include $(DEPS)
 
%.o: %.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@
 
squareception: $(OBJS)
	gcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@
 
clean:
	rm -f $(OBJS) $(DEPS) squareception

//cc src/app.c src/main.c -Iinclude -Llibs/x86_64-linux-gnu -lglfw3 -lcanvas -lstdc++ -ldl -lm -lpthread -o app