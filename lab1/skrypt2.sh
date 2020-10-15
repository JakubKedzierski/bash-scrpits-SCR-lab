#!/bin/bash
#10 - Wywolanie $0 nazwa katalogu, nazwa pliku

if test "$#" -ne 3 ; then
echo "Nieprawidlowe wywolanie. Prawidlowe wywolanie $0 [nazwa nowego katalogu] [nazwa nowego pliku] [Maska do szukania pliku] "
exit 1
fi

if test -d "$1" ; then
rm -r "$1"
fi

echo "Utworzyc katalog $1 [y/n] ?"
read ANS1

if test "$ANS1"="y" ; then
mkdir "$1"
cd "$1" 
fi

echo "Utworzyc plik $2 [y/n] ?"
read ANS2

if test "$ANS2"="y" ; then
touch plik.c
mv plik.c "$2"
fi

if test "$ANS1"="y" ; then
cd ..
fi

find . -name "$3" -type f

#do 11: sudo find /etc -type f \( -mtime +5 -a -mtime -40 -a -size -250k \) -o \( -mtime -5 -a -size -3k \)
#do 12: rozpakowanie tar -xf pakowanie tar - cjf // jak sie poda pelna sciezke to z folderami pakuje, gdy bez sciezki pakuje same pliki
# -C pokazuje katalog docelowy na rozpakowanie


