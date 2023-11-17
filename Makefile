# Makefile for Spoinkstore

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra `pkg-config --cflags gtk+-3.0` `pkg-config --cflags json-glib-1.0`

# Source files
SRC := main.cpp  # Add your source files here

# Object files
OBJ := $(SRC:.cpp=.o)

# Target executable
TARGET := spoinkstore

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ `pkg-config --libs gtk+-3.0` `pkg-config --libs json-glib-1.0`

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)/usr/local/bin/$(TARGET)

uninstall:
	rm -f $(DESTDIR)/usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
