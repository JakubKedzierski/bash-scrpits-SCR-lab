#!/bin/bash
#Przykladowe wywolanie ./czwarty.sh -m *.c -n 20 

usage(){ printf "Poprawne wywolanie: \n $0 [-n liczba dni od modyfikacji] [-m maska] [-a nazwa awrchiwum] \n \n" ;}

while getopts "n:m:a:" OPTION
do 
case $OPTION in
n) N=$OPTARG;;
m) MASK=$OPTARG;;
a) NAME=$OPTARG;;
*) usage; exit 1;;
esac
done

if test -z "$N" ; then
    echo "Nie zostal podany parametr [-n liczba dni od modyfikacji]. Podaj wartosc parametru:"
    read N
fi

if test -z "$MASK" ; then
    echo "Nie zostal podany parametr  [-m maska]. Podaj wartosc parametru:"
    read MASK
fi

if test -z "$NAME" ; then
    echo "Nie zostal podany parametr [-a nazwa awrchiwum]. Podaj wartosc parametru:"
    read NAME
fi

tar -cjf "$NAME" `find . -type f -name "$MASK" -mtime -"$N" `

