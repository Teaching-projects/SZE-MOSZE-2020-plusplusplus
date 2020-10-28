SHELL=/bin/bash

OBJS = JSON.o Hero.o Monster.o main.o
OUT = a.out
CFLAGS = -Wall -std=c++17
CC = g++-9

default: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

run: ./$(OUT)
	./$(OUT) $(SCENARIO)

Hero.o: Hero.cpp Hero.h JSON.h jsonFileReadError.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h Hero.h JSON.h jsonFileReadError.h
	$(CC) $(CFLAGS) -c Monster.cpp

JSON.o: JSON.cpp JSON.h jsonFileReadError.h
	$(CC) $(CFLAGS) -c JSON.cpp

main.o: main.cpp Hero.h Monster.h JSON.h jsonFileReadError.h
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
