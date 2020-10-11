#!/bin/bash

IFS=$'\n'
run_program="$(./a.out units/unit1.json units/unit2.json)"
memory_leak_check_cmd="$(valgrind --leak-check=yes --log-file=memory_leak_check.txt $run_program)"
echo $memory_leak_check_cmd
memory_leak_check_result="$(cat ./memory_leak_check.txt)"
detected_errors="$(echo $memory_check_result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')"
expected_errors="0"
if [ "$expected_errors" == "$detected_errors" ]
then
    echo "No memory leak(s) found."
else
    echo "Memory leak(s) found. Quitting."
    exit 1
fi
