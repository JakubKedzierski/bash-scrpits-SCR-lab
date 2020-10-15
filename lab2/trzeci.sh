#!/bin/bash
#Wywolanie np. ./trzeci.sh tarowany.tar 10 *.c

named=$1
N=$2
mask=$3

if test "$#" -ne 3 ; then
    echo "Nieprawidlowe wywolanie. Porawne wywolanie $0 [nazwa archiwum] [liczba dni od modyfikacji] [maska]"
    exit 1
fi

tar -cjf $named `find . -type f -name "$mask" -mtime -$N ` 