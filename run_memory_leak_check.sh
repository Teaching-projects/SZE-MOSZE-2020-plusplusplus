#!/bin/bash

check="$(valgrind --log-file=memory_leak.txt)"
echo $check
if [ -s ./memory_leak.txt ]
then
    echo "Memory leak found."
    exit 1
else
    echo "No memory leak found."
    echo
fi
