#!/bin/bash

# Build the main.cpp file
g++ -c main.cpp -std=c++11 -Wall -Wextra -pedantic -fPIC -I/usr/include/qt5 -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtNetwork

# Link the object file to create the executable
g++ -o SpoinkStore main.o -ljsoncpp -lcurl -lQt5Core -lQt5Widgets -lQt5Network

# Clean up object file
rm main.o
