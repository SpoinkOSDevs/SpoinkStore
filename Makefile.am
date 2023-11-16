# Makefile for Spoinkstore

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra `pkg-config --cflags gtk+-3.0`

# Source files
SRC := main.cpp  # Add your source files here

# Object files
OBJ := $(SRC:.cpp=.o)

# Target executable
TARGET := spoinkstore

# Installation directory
INSTALL_DIR := /usr/local/bin

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ `pkg-config --libs gtk+-3.0`

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(INSTALL_DIR)/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
