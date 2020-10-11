#!/bin/bash

cmd="$(cppcheck *.cpp --enable=warning --output-file=code_analysis_primary.txt)"
echo $cmd
if [ -s ./code_analysis_primary.txt ]
then
    echo "Errors or/and warnings found."
    exit 1
else
    echo "No problems found."
    echo
fi
