#!/bin/bash

usage(){ printf "Poprawne wywolanie: \n $0 [-n liczba dni modyfikacji] [-m maska] [-a nazwa awrchiwum] \n \n" ;}

while getopts "n:m:a:" OPTION
do 
case $OPTION in
n) N=$OPTARG;;
m) MASK=$OPTARG;;
a) NAME=$OPTARG;;
*) usage; exit 1;;
esac
done

tar -cjf $NAME `find . -type f -name "$MASK" -mtime -$N`

