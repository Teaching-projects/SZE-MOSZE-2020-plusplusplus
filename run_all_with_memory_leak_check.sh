#!/bin/bash

run_program="./a.out units/unit1.json units/unit2.json";
cmd="$(valgrind -v --log-file=memory_leak_check.txt $run_program)"
echo $cmd
