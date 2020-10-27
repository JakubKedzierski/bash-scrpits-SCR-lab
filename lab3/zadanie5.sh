#!/bin/bash
k=0
for k in {1..64} ; do
    trap 'echo przechwycone ' $k
done 

i=0
while test $i -lt 1000 ; do
    date +%T
    i=$((i+1))
    sleep 5
done

#kill -s SIGFPE `pgrep zadanie5.sh`  -> sygnaly sa przechwytywane
# SIGKILL zabija pomimo wszystko, SIGSTOP i SIGCONT nie sa przechwytywane moze to wynikac ze stosowania bash
# 64 sygnaly (trap -l)