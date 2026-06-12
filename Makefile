# ===== raylib Makefile: one binary per .c file (great for examples) =====
# Usage:
#   make                 -> build ALL examples in src/
#   make build/core_basic_window   -> build just that one
#   make run NAME=core_basic_window -> build + run just that one
#   make list            -> list available examples
#   make clean           -> remove build/
SRC_DIR   := src
BUILD_DIR := build

UNAME_S := $(shell uname -s)

CFLAGS  := -std=c99 -Wall -Wextra -g -O0 -I. -MMD -MP

ifeq ($(UNAME_S),Darwin)
    CC      := clang
    UNAME_M := $(shell uname -m)
    ifeq ($(UNAME_M),arm64)
        BREW_PREFIX := /opt/homebrew
    else
        BREW_PREFIX := /usr/local
    endif
    CFLAGS  += -I$(BREW_PREFIX)/include
    LDLIBS  := -L$(BREW_PREFIX)/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
else
    CC      := gcc
    LDLIBS  := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

SRCS    := $(wildcard $(SRC_DIR)/*.c)
BINS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))
DEPS    := $(BINS:=.d)

.PHONY: all run list clean

all: $(BINS)

# Build each source file into its own executable
$(BUILD_DIR)/%: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)
	@echo ">> Built $@"

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build + run a single example:  make run NAME=core_basic_window
run: $(BUILD_DIR)/$(NAME)
	@./$(BUILD_DIR)/$(NAME)

# Show all examples you can build/run
list:
	@echo "Available examples:"
	@ls -1 $(SRC_DIR)/*.c 2>/dev/null | sed 's|$(SRC_DIR)/||; s|\.c$$||' | sed 's|^|  - |'

clean:
	@rm -rf $(BUILD_DIR)
	@echo ">> Cleaned"

-include $(DEPS)
