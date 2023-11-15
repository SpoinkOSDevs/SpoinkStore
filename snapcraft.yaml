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

# Installation directory
INSTALL_DIR := /usr/local/bin

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(INSTALL_DIR)/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
