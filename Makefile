# Compiler settings
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -Iinclude

# Build directory
BUILD_DIR := build

# Sources
COMMON_SRCS := src/rb_tree.c src/auxiliary.c
MAIN_SRC    := src/main.c
TEST_SRC    := tests/test_rbtree.c

# Object files
COMMON_OBJS := $(COMMON_SRCS:src/%.c=$(BUILD_DIR)/%.o)
MAIN_OBJ    := $(MAIN_SRC:src/%.c=$(BUILD_DIR)/%.o)
TEST_OBJ    := $(TEST_SRC:tests/%.c=$(BUILD_DIR)/%.o)

# Targets
TARGET       := rbtree
TEST_TARGET  := rbtree_test

.PHONY: all clean

all: $(TARGET) $(TEST_TARGET)

# Link interactive binary
$(TARGET): $(COMMON_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Link test binary
$(TEST_TARGET): $(COMMON_OBJS) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile common and main sources
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test source
$(BUILD_DIR)/%.o: tests/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) 
	rm -rf $(TARGET) 
	rm -rf $(TEST_TARGET)

