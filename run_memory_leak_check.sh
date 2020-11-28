#!/bin/bash

IFS=$'\n'
memory_leak_check_cmd="$(valgrind --leak-check=yes --log-file=memory_leak_check.txt ./a.out scenarios/scenario1.json < input.txt)"
memory_leak_check_result="$(cat ./memory_leak_check.txt)"
echo $memory_leak_check_result
detected_errors="$(echo $memory_leak_check_result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')"
expected_errors="0"
if [ "$expected_errors" == "$detected_errors" ]
then
    echo
    echo "No memory leak(s) found."
else
    echo "Memory leak(s) found. Quitting."
    exit 1
fi
