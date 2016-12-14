#!/bin/bash
gcc pi_series_omp.c -fopenmp
rm omp.txt
for x in 1 2 4 8 16 32 
do
	for input in 10000  100000  1000000 10000000 100000000 1000000000 10000000000 
	do
	./a.out $input $x >> omp.txt 
	done
done

