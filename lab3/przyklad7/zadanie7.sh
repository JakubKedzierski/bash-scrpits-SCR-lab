#!/bin/bash
i=1
k=1
while true ; do
    i=$((i+1))
    j=1
    while test $j -eq $i ; do
        k=$((k*i))
        j=$((i+1))
    done
done