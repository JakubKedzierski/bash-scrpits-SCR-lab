#!/bin/bash

path="./plikiDoDrugiego"
subject="Oferta_przetargowa"

for address in $(cat $path/adresy.txt)
do
    mutt -s $subject $address -a $path/spec*.pdf < $path/tresc.txt 
done
