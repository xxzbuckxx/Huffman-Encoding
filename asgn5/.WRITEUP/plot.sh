#!/bin/bash
cd ../ && make clean all
typeset -i n
echo "" > /tmp/entropy.dat
echo "" > /tmp/entropy_encoded.dat
for fp in $(seq 0 0.001 1); do
	ENTROPY=$(cat $1 | ./error -e $fp | ./entropy)
	ENTROPY_ENCODED=$(./encode < $1 | ./error -e $fp | ./entropy)
	echo "$fp $ENTROPY" >> /tmp/entropy.dat
	echo "$fp $ENTROPY_ENCODED" >> /tmp/entropy_encoded.dat
done
make clean & cd .WRITEUP/graphs
gnuplot <<XX
set terminal jpeg size 900, 600
set pointsize 0.2
set title "Entropy vs Noise in ${2}"
set xlabel "Percent Noise"
set ylabel "Entropy"
show title
show xlabel
show ylabel
set xtics 0,0.1,1

set key top right

set output "${2}.entropy.jpg"
plot "/tmp/entropy.dat" with points lc rgbcolor "#46237A" title "original entropy", \
	 "/tmp/entropy_encoded.dat" with points lc rgbcolor "#1ed448" title "encoded entropy"
	
