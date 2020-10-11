#!/bin/bash

results="../out/results"
cmd="$(cppcheck ../*.cpp --enable=warning --output-file=$results/code_analysis_primary.txt)"
echo $cmd
if [ -s $results/code_analysis_primary.txt ]
then
    echo "Errors or/and warnings found."
    exit 1
else
    echo "No problems found."
    echo
fi
