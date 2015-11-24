#!/usr/bin/env bash

file="$1"

#echo ${file}

g++ ${file}.cpp -o bin/${file}.o -g
chmod +x bin/${file}.o
./bin/${file}.o
