SHELL=/bin/bash

OBJS = JSON.o Unit.o Hero.o Monster.o main.o
OUT = a.out
CFLAGS = -Wall -Wextra -std=c++17
CC = g++-9

default: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

run: ./$(OUT)
	./$(OUT) $(SCENARIO)

Unit.o: Unit.cpp Unit.h
	$(CC) $(CFLAGS) -c Unit.cpp

Hero.o: Hero.cpp Hero.h Unit.h JSON.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h Unit.h JSON.h
	$(CC) $(CFLAGS) -c Monster.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

main.o: main.cpp Hero.h Monster.h JSON.h
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

unittest:
	cd tests && cmake .
	cd tests && make
	cd tests && ./tests
	
clean:
	rm -rf $(OBJS) $(OUT)
