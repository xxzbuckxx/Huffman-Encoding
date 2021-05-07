#!/bin/bash
cd ../ && make clean all
typeset -i n
echo "" > /tmp/${2}_entropy.dat
for fp in $(seq 0 0.001 1); do
	ENTROPY=$(./encode < $1 | ./error -e $fp | ./entropy)
	echo "$fp $ENTROPY" >> /tmp/${2}_entropy.dat
done
make clean & cd .WRITEUP/graphs
gnuplot <<XX
set terminal jpeg size 900, 600
set pointsize 0.2
set title "Entropy vs Noise"
set xlabel "Percent Noise"
set ylabel "Entropy"
show title
show xlabel
show ylabel
# set xrange [0:1000]

set key top right

set output "${2}_entropy.jpg"
plot "/tmp/${2}_entropy.dat" with points lc rgbcolor "#46237A" title "${2} file entropy"
