#!/bin/bash
#9

set "probny"

if test -d "$1" ; then
rm -r "$1"
fi

mkdir "$1"
cd "$1" 
touch plik.c
mv plik.c inny.c
cd ..
