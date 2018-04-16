#!/bin/bash
set term jpeg large
set out "wynik_2.jpg"
set xlabel "k"
set ylabel "x(k)"

set grid
set key top
plot "wektory_wlasne_alfa0.dat" u 1:2 w l t "1","wektory_wlasne_alfa100.dat"  u 1:2 w l t "2"