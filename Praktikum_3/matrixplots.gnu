reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"col.txt" with linespoints title 'ColMajor',\
"row.txt" with linespoints title 'RowMajor',\
"colomp.txt" with linespoints title 'ColMajorOMP',\
"rowomp.txt" with linespoints title 'RowMajorOMP',\
