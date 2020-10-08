#!/bin/bash

check="$(cppcheck *.cpp --enable=performance,style --output-file=perf_and_style_analysis.txt)"
echo $check
if [ -s ./perf_and_style_analysis.txt ]
then
    echo "Performance or/and style problems found."
else
    echo "No performance or style problems found."
fi
echo
