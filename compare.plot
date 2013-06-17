set terminal post eps
set output "comparison.eps"
set multiplot
plot "results/square.results" using 1:2 title 'square' with points lc rgb "red", \
"results/rhombus.results" using 1:2 title 'rhombus' with points lc rgb "blue", \
"results/rectangle.results" using 1:2 title 'rectangle' with points lc rgb "green"
