#!/bin/bash
mpicc pi_series_mpi.c
rm mpi.txt
for x in 1 2 4 8 16 32 
do
	for input in 10000  100000  1000000 10000000 100000000 1000000000 10000000000 
	do
	mpirun -np $x ./a.out $input >> mpi.txt 
	done
done

