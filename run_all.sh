#!/bin/bash

while IFS= read -r line
do
    readarray -d \; -t data <<<"$line"
    expect="$(sed 's/^[[:space:]]*//g'<<<${data[2]})"
    echo "Player 1: ${data[0]}"
    echo "Player 2: ${data[1]}"
    echo "Expected Result: \"${expect}\""
    real="$(valgrind --leak-check=yes --exit-on-first-error=yes --error-exitcode=1 --log-file=memory_leak_check.txt ./a.out units/${data[0]} units/${data[1]})"
    echo "Real Result: \"$real\""
    if [ "$expect" == "$real" ]
    then
        echo "Test success."
        echo
    else
        echo "Test fail. Quitting."
        exit 1
    fi
done < "./units/expected_results.csv"