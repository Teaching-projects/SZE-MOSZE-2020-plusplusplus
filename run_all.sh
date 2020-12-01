#!/bin/bash

lines=()
count=0

while IFS= read -r line
do
    lines+=("$line")
    count=$((count+1))
done < "./scenarios/expected_results.csv"

for (( i=0; i<count; i++))
do
    readarray -d \; -t data <<<"${lines[$i]}"
    c=${data[1]}
    expect=""
    for (( j=i+1; j<=i+c; j++))
    do
        if [ $j -eq $((i+1)) ]
        then
            expect="${lines[$j]}"
        else
            expect="$expect\n${lines[$j]}"
        fi
    done
    expect=$(echo -e "$expect")
    echo "Scenario: ${data[0]}"
    echo "Expected Result: \"${expect}\""
    real="$(./a.out scenario scenarios/${data[0]} < input.txt 2> /dev/null)"
    echo "Real Result: \"$real\""

    if [ "$real" = "$expect" ]
    then
        echo "Test success."
        echo
    else
        echo "Test fail. Quitting."
        exit 1
    fi
    
    i=$((i+c))
done