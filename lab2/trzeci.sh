#!/bin/bash
#Wywolanie np. ./trzeci.sh tarowany.tar 10 *.c

named=$1
N=$2
mask=$3

tar -cjf $named `find . -type f -name "$mask" -mtime -$N ` 