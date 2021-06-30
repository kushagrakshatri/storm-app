CC = g++
CFLAGS = -std=c++11

all:storm
	$(CC) $(CFLAGS) -o storm storm.cpp