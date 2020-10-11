#!/bin/bash

IFS=$'\n'
run_all="$(./run_all.sh)"
memory_check_result="$(cat ./memory_leak_check.txt)"
detected_errors="$(echo $memory_check_result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')"
expected_errors="0"
if [ "$expected_errors" == "$detected_errors" ]
then
    echo "No memory leak(s) found."
else
    echo "Memory leak(s) found. Quitting."
    exit 1
fi
