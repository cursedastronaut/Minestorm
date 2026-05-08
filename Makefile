PROGRAM := minestorm

# Detect platform
ifeq ($(OS),Windows_NT)
	EXEEXT := .exe
	RM := del /Q /F
	RMDIR := rmdir /S /Q
	MKDIR_P = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
	LIBEXT := .a
else
	EXEEXT :=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR_P = mkdir -p "$1"
	LIBEXT := .a
endif

# Paths
LIBS_PATH := libs/
OBJDIR := objects
MINIAUDIO_DIR := libs/miniaudio
MINIAUDIO_SRC := $(MINIAUDIO_DIR)/miniaudio.c
#MINIAUDIO_OBJ := $(OBJDIR)/libs/miniaudio/miniaudio.o
MINIAUDIO_LIB := $(LIBS_PATH)libminiaudio$(LIBEXT)

# Tools
CC := gcc
AR := ar rcs

# Flags
CFLAGS := -Ofast -g3 -D_DEBUG
CPPFLAGS := -Iinclude/ -Iinclude/libs/ -Iinclude/
DEPFLAGS := -MMD -MP

LDFLAGS := -L$(LIBS_PATH)x86_64-linux-gnu -L$(LIBS_PATH)
LDLIBS := -lglfw3 -lcanvas -lminiaudio -lstdc++ -ldl -lpthread -lm

# Sources
CSRC := $(wildcard src/*.c) \
        $(wildcard src/**/*.c) \
        $(wildcard src/**/**/*.c) \
        $(wildcard src/**/**/**/*.c)

# Object + dependency mapping
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(CSRC))
DEPS := $(OBJS:.o=.d)
#MINIAUDIO_DEP := $(MINIAUDIO_OBJ:.o=.d)

.PHONY: all clean fclean re

all: $(PROGRAM)$(EXEEXT)

# Include dependency files
-include $(DEPS)

# Build executable
$(PROGRAM)$(EXEEXT): $(MINIAUDIO_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# Build miniaudio static library
$(MINIAUDIO_LIB):
	@$(call MKDIR_P,$(LIBS_PATH))
	@$(call MKDIR_P,$(OBJDIR)/libs/miniaudio/)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(MINIAUDIO_SRC) -o $(OBJDIR)/libs/miniaudio/miniaudio.o
	$(AR) $@ $(OBJDIR)/libs/miniaudio/miniaudio.o

# Generic source compilation
$(OBJDIR)/%.o: %.c
	@$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean objects only
clean:
ifeq ($(OS),Windows_NT)
	-$(RMDIR) $(OBJDIR)
else
	$(RMDIR) $(OBJDIR)
endif

# Full clean
fclean: clean
ifeq ($(OS),Windows_NT)
	-$(RM) $(PROGRAM)$(EXEEXT) config.bin $(MINIAUDIO_LIB)
else
	$(RM) $(PROGRAM)$(EXEEXT) config.bin $(MINIAUDIO_LIB)
endif

# Rebuild
re: fclean all