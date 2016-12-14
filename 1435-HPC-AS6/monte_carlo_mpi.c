#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char **argv){
	
	long n = atol(argv[1]), i;
	int my_rank, num_cpus;
	int print = atoi(argv[2]);
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_cpus);
	long local_n = n / num_cpus;
	
	double x, y;
	long count = 0, local_count = 0;
	
	srand(time(NULL));
	double start = MPI_Wtime();
	
	for(i = 0; i < local_n; i++){
		x = 2.0 * (double) rand() / (double) RAND_MAX - 1.0;
		y = 2.0 * (double) rand() / (double) RAND_MAX - 1.0;
		
		if(x * x + y * y <= 1.0) local_count++;
	}
	
	
	MPI_Reduce(&local_count, &count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(my_rank == 0){
		double end = MPI_Wtime();
		double total = end - start, PI = ((double)count * 4.0 )/ (double) n;
		if(print == 1)
			printf("CPUs: %d, Time taken for n = %ld is %lf, PI = %lf\n", num_cpus, n, total, PI);
		else
			printf("%d %ld %lf %lf\n", num_cpus, n, total, PI);
	}
}
