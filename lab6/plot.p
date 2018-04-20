#!/bin/bash
set term jpeg large
set out "wynik_1.jpg"
set xlabel "Real"
set ylabel "Image"

plot "rys.dat" u 1:2 w l t "1","" u 3:4 w l t "2","" u 5:6 w l t "3","" u 7:8 w l t "4"