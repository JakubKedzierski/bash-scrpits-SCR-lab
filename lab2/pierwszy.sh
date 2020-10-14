#!/bin/bash

#LC_ALL - zmienna srodowiskowa nadpisujaca pozostale zmienne lokalne, czyli np czas, sortowanie, jezyk itp
# C - ustawia na domyslne wartosci, dopasowane np do bibliotek systemowych

LC_ALL=C
dayOfWeek=$(date +%u)

if test "$dayOfWeek" -gt 5 ; then
    echo "Witaj"
else
    echo "Dzien dobry"
fi
