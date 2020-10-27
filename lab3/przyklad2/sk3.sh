#!/bin/bash
echo "czwarty"
i=0

while test "$i" -lt 100 ; do
    echo "Czekam $i"
    i=$[i+1]
    sleep 30
done