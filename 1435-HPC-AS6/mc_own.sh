#!bin/bash/
rm mc_own.txt
gcc mc_own.c -lm -fopenmp
#c=0
#sum=0
count=0

#for bs in 4 64 128
	#do				
		for p in 2 4 8 16 32   
				do
						
					echo "p is : $p">>"own.txt"
						for N in 1000 10000 100000 1000000 10000000 100000000
							do	#echo "N is $N"
								c=0
								sum=0 
								while [ $c -lt 11 ]
								do 
								count=$(./a.out $p $N)
							
								c=`expr $c + 1`
								
								sum=`echo $sum + $count | bc`
								#echo "sum is $sum"
								
								done
							#echo "sum is $sum"
							avg=$(echo "$sum/$c" | bc -l)
							#echo $avg
							echo "$avg">> "mc_own.txt"
						done
				done  
	#done
