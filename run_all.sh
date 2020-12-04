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
    real="$(./build/game.out scenario scenarios/${data[0]} < input.txt 2> /dev/null)"

    if [ "$real" = "$expect" ]
    then
        echo "Test success."
        echo
    else
        echo "Expected Result: \"${expect}\""
        echo "Real Result: \"$real\""
        echo "Test fail. Quitting."
        exit 1
    fi
    
    i=$((i+c))
done

lines=()
count=0

while IFS= read -r line
do
    lines+=("$line")
    count=$((count+1))
done < "./prepare/expected_results.csv"

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
    real="$(./build/game.out prepare prepare/${data[0]} < prepare/input 2> /dev/null)"

    if [ "$real" = "$expect" ]
    then
        echo "Test success."
        echo
    else
        echo "Real Result: \"$real\""
        echo "Expected Result: \"${expect}\""
        echo "Test fail. Quitting."
        exit 1
    fi
    
    i=$((i+c))
done