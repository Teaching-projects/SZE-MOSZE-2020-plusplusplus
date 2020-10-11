#!/bin/bash

check="$(cppcheck *.cpp --enable=warning --output-file=error_and_warning_analysis.txt)"
echo $check
if [ -s ./error_and_warning_analysis.txt ]
then
    echo "Errors or/and warnings found."
    exit 1
else
    echo "No problems found."
    echo
fi
