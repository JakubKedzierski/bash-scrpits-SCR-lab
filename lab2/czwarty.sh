#!/bin/bash

usage(){ printf "Poprawne wywolanie: \n $0 [-n liczba dni modyfikacji] [-m maska] [-a nazwa awrchiwum] \n \n" ;}

while getopts "n:ma" OPTION
do 
case $OPTION in
n) echo n;;
m) echo k;;
a) echo a;;
*) usage; exit 1;;
esac
done

