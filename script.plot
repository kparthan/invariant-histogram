set terminal post eps
set output "test/square.eps"
set multiplot
plot "test/square.actual" using 1:2 title 'actual' with points lc rgb "red", \
"test/square.samples" using 1:2 title 'samples' with points lc rgb "blue"
