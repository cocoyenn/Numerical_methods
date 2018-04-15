#!/bin/bash
set term jpeg large
set out "wynik_1.jpg"
set xlabel "Real x"
set ylabel "Imag y"

set grid 
set key top 
plot "zj_0_0I.dat" u 3:4 w l 