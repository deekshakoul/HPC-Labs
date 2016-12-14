#!bin/bash/
rm own.txt
gcc mc_own.c -lm -fopenmp
for n in 1 4 8 16
do
	for N in 1000 10000 100000 1000000 10000000 100000000
 do
	./a.out $n $N >> own.txt
  done
done  
