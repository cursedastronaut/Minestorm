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

# ------------------------------------------------------------------
# Directories
# ------------------------------------------------------------------
OBJDIR := objects

# ------------------------------------------------------------------
# Submodules
# ------------------------------------------------------------------
LIBCANVAS_DIR := third-party/libcanvas
MINIAUDIO_DIR := third-party/miniaudio

LIBCANVAS_LIB := $(LIBCANVAS_DIR)/libcanvas$(LIBEXT)

MINIAUDIO_SRC := $(MINIAUDIO_DIR)/miniaudio.c
MINIAUDIO_OBJ := $(OBJDIR)/third-party/miniaudio/miniaudio.o
MINIAUDIO_LIB := $(MINIAUDIO_DIR)/libminiaudio$(LIBEXT)

# ------------------------------------------------------------------
# Tools
# ------------------------------------------------------------------
CC := gcc
AR := ar rcs
MAKE := make
GIT := git

# ------------------------------------------------------------------
# Flags
# ------------------------------------------------------------------
CFLAGS := -Ofast -g3 -D_DEBUG

CPPFLAGS := \
	-Iinclude/ \
	-I$(LIBCANVAS_DIR)/include/ \
	-I$(MINIAUDIO_DIR)/ \
	-I$(LIBCANVAS_DIR)/third_party/cimgui/ \
	-I$(LIBCANVAS_DIR)/third_party/cimgui/imgui/ \
	-I$(LIBCANVAS_DIR)/third_party/cimgui/imgui/backends/

DEPFLAGS := -MMD -MP

LDFLAGS :=

LDLIBS := \
	-lcanvas \
	-lminiaudio \
	-lglfw3 \
	-lstdc++ \
	-ldl \
	-lpthread \
	-lm	\
	-L$(LIBCANVAS_DIR) \
	-L$(MINIAUDIO_DIR) \
	-Llibs/x86_64-pc-linux-gnu  \
	-Llibs/x86_64-w64-mingw32 \
	-Llibs/x86_64-pc-cygwin \
	-Llibs/x86_64-linux-gnu

# ------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------
CSRC := $(wildcard src/*.c) \
        $(wildcard src/**/*.c) \
        $(wildcard src/**/**/*.c) \
        $(wildcard src/**/**/**/*.c)

# ------------------------------------------------------------------
# Objects + dependencies
# ------------------------------------------------------------------
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(CSRC))
DEPS := $(OBJS:.o=.d)
MINIAUDIO_DEP := $(MINIAUDIO_OBJ:.o=.d)

# ------------------------------------------------------------------
# Phony targets
# ------------------------------------------------------------------
.PHONY: all clean fclean re submodules

# ------------------------------------------------------------------
# Default target
# ------------------------------------------------------------------
all: submodules $(PROGRAM)$(EXEEXT)

# ------------------------------------------------------------------
# Include dependency files
# ------------------------------------------------------------------
-include $(DEPS) $(MINIAUDIO_DEP)

# ------------------------------------------------------------------
# Submodule initialization
# ------------------------------------------------------------------
submodules:
	@echo "Checking submodules..."
	@if [ ! -f "$(LIBCANVAS_DIR)/Makefile" ] || [ ! -f "$(MINIAUDIO_DIR)/miniaudio.h" ]; then \
		echo "Initializing missing submodules..."; \
		$(GIT) submodule update --init --recursive; \
	fi

# ------------------------------------------------------------------
# Final executable
# ------------------------------------------------------------------
$(PROGRAM)$(EXEEXT): $(LIBCANVAS_LIB) $(MINIAUDIO_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# ------------------------------------------------------------------
# Build libcanvas
# ------------------------------------------------------------------
$(LIBCANVAS_LIB): submodules
	$(MAKE) -C $(LIBCANVAS_DIR)

# ------------------------------------------------------------------
# Build miniaudio static library
# ------------------------------------------------------------------
$(MINIAUDIO_LIB): $(MINIAUDIO_SRC) $(MINIAUDIO_DIR)/miniaudio.h
	@$(call MKDIR_P,$(dir $(MINIAUDIO_OBJ)))
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $(MINIAUDIO_SRC) -o $(MINIAUDIO_OBJ)
	$(AR) $@ $(MINIAUDIO_OBJ)

# ------------------------------------------------------------------
# Generic source compilation
# ------------------------------------------------------------------
$(OBJDIR)/%.o: %.c
	@$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

# ------------------------------------------------------------------
# Clean objects
# ------------------------------------------------------------------
clean:
ifeq ($(OS),Windows_NT)
	-$(RMDIR) $(OBJDIR)
else
	$(RMDIR) $(OBJDIR)
endif

# ------------------------------------------------------------------
# Full clean
# ------------------------------------------------------------------
fclean: clean
	$(MAKE) -C $(LIBCANVAS_DIR) clean
ifeq ($(OS),Windows_NT)
	-$(RM) $(PROGRAM)$(EXEEXT) config.bin $(MINIAUDIO_LIB)
else
	$(RM) $(PROGRAM)$(EXEEXT) config.bin $(MINIAUDIO_LIB)
endif

# ------------------------------------------------------------------
# Rebuild
# ------------------------------------------------------------------
re: fclean all