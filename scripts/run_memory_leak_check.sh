#!/bin/bash

echo $check
check="$(valgrind --tool=memcheck --log-file=memory_leak.txt)"
if [ -s ./memory_leak.txt ]
then
    echo "Memory leak found."
    exit 1
else
    echo "No memory leak found."
    echo
fi
