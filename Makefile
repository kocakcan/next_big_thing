PROJECT_NAME := game
SRC_DIR      := src
BUILD_DIR    := build
SRCS         := $(wildcard $(SRC_DIR)/*.c)
OBJS         := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS         := $(OBJS:.o=.d)

CC      := gcc
CFLAGS  := -std=c99 -Wall -Wextra -g -O0 -I. -MMD -MP
LDFLAGS :=
LDLIBS  := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET := $(BUILD_DIR)/$(PROJECT_NAME)

.PHONY: all run release clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@echo ">> Built $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

run: all
	./$(TARGET)

release: CFLAGS := -std=c99 -Wall -O2 -DNDEBUG -I.
release: clean all

clean:
	@rm -rf $(BUILD_DIR)
	@echo ">> Cleaned"

-include $(DEPS)
