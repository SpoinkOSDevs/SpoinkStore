# Makefile for Spoinkstore

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra

# Source files
SRC := main.c  # Add your source files here

# Object files
OBJ := $(SRC:.c=.o)

# Target executable
TARGET := spoinkstore

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
