#!/bin/bash

programs=("test_vector_addition.cpp" "test_vector_addition_static.cpp")

size=$1
repeat=$2


#clang++ -fjit  -o "${programs[0]%.cpp}" "${programs[0]}"
#clang++  -o "${programs[1]%.cpp}" "${programs[1]}"

for prog in "${programs[@]}"
do
    name="${prog%.cpp}"
    ./"$name" "$size" "$repeat"
done
