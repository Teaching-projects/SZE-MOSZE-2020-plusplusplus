#!/bin/bash

cmd="$(cppcheck *.cpp --enable=performance,style --output-file=code_analysis_secondary.txt)"
echo $cmd
if [ -s ./code_analysis_secondary.txt ]
then
    echo "Performance or/and style problems found."
else
    echo "No performance or style problems found."
fi
