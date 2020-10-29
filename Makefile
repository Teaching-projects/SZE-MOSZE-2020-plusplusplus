SHELL=/bin/bash

OBJS = json.o player.o loop.o main.o
OUT = a.out
CFLAGS = -Wall -std=c++17
CC = g++

default: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

loop.o: loop.cpp
	$(CC) $(CFLAGS) -c loop.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) -c player.cpp

json.o: json.cpp
	$(CC) $(CFLAGS) -c json.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

test:
	bash -c "./run_all.sh"

memory_leak_check:
	bash -c "./run_memory_leak_check.sh"

static_code_analysis:
	bash -c "./run_code_analysis_primary.sh"
	bash -c "./run_code_analysis_secondary.sh"

documentation:
	doxygen doxygenconf

clean:
	rm -rf $(OBJS) $(OUT)
