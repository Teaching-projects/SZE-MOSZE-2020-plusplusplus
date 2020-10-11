#!/bin/bash

run_program="./a.out units/unit1.json units/unit2.json";
cmd="$(valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 --log-file=memory_leak_check.txt $run_program)"
echo $cmd
