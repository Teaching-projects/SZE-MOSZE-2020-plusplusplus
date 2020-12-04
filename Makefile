SHELL=/bin/bash

OUT = build/game.out

default: build

build:
	cd build; cmake .; make

rebuild:
	cd build; make

run: ./$(OUT)
	./$(OUT) $(MODE) $(FILE)
	
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
	rm -rf code_analysis*.txt memory_leak_*.txt
	cd build; make clean
	cd tests; make clean
