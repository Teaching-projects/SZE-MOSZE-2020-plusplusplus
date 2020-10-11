#!/bin/bash

scripts="../scripts"
results="../out/results"
cmd="$(valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=$results/memory_leak.txt $scripts/run_all.sh)"
echo $cmd
if [ -s $results/memory_leak.txt ]
then
    echo "Memory leak(s) found."
    exit 1
else
    echo "No memory leak found."
    echo
fi
