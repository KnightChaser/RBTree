CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
SRC     := src/rb_tree.c src/auxiliary.c src/main.c
OBJ     := $(SRC:src/%.c=build/%.o)
TARGET  := rbtree

all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

