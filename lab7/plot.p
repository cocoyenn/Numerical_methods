#!/bin/bash
set term jpeg large
set out "wynik_n_cz_20.jpg"
set xlabel " x"
set ylabel "y"

set grid 
set key top 
plot "n_cz_20.dat" u 1:2 w l t "W(x) n=20", "" u 1:3 w l t "e^(-x^2)" 