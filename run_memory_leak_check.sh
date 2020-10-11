#!/bin/bash

cmd="$(valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 --log-file=memory_leak_check.txt ./run_all.sh)"
echo $cmd
