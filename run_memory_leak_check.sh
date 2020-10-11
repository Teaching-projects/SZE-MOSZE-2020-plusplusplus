#!/bin/bash

cmd="$(valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=memory_leak.txt ./run_all.sh)"
echo $cmd
if [ -s ./memory_leak.txt ]
then
    echo "Memory leak(s) found."
    exit 1
else
    echo "No memory leak found."
    echo
fi
