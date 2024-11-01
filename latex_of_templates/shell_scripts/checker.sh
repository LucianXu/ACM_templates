#!/bin/bash

cd "$1"

g++ −o main −O2 −std=c++17 −DLOCAL main.cpp −ftrapv −fsanitize=address,undefined

for input in *.in; do
    output=${input%.*}.out
    answer=${input%.*}.ans

    ./main < $input > $ouput

    echo "case ${input%.*}: "
    echo "My: "
    cat $output
    echo "Answer: "
    cat $answer

done