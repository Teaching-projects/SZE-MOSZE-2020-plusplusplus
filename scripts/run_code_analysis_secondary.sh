#!/bin/bash

root=".."
results="../out/results"
cmd="$(cppcheck $root/*.cpp --enable=performance,style --output-file=$results/code_analysis_secondary.txt)"
echo $cmd
if [ -s $results/code_analysis_secondary.txt ]
then
    echo "Performance or/and style problems found."
else
    echo "No performance or style problems found."
fi
echo
