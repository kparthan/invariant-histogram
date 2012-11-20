# Gnuplot script script for plotting global histogram values
# for different values of r

set terminal png small
set autoscale # scale axes automatically
set xtic auto # set xtics automatically
set ytic auto # set ytics automatically
set title "COMPARISON OF GLOBAL HISTOGRAM FUNCTIONS\n[Number of samples = 497]"
set xlabel "r"
set ylabel "global histogram value"
set xr [0:50]
set yr [0:1.2]
set output "comparison.png"
set multiplot
plot "results.txt" using 1:2 title '1hhoa' \
with points lc rgb "red", \
"results.txt" using 1:3 title '1idr' \
with points lc rgb "blue", \
"results.txt" using 1:4 title '1mbd' \
with points lc rgb "green", \
"results.txt" using 1:5 title '2snv' \
with points lc rgb "brown"