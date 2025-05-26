CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
SRC     := src/rb_tree.c src/main.c
OBJ     := $(SRC:.c=.o)
TARGET  := rbtree

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

