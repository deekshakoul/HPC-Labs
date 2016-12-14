#include <mpi.h>
#include <stdio.h>

//double MPI_Wtime ( );
int main(int argc, char **argv)
{
	long num_steps = atol(argv[1]);
	int my_rank, num_cpus;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_cpus);
	MPI_Status status;
	int factor = 1.0;
	//printf("Hello, I am process %d among %d processes and number of steps is %ld \n",my_rank, num_cpus,num_steps);
	double pi;
	double sum1 = 0.0, sum = 0.0;
	int i = 0;
	
	double start = MPI_Wtime();
		
	for(i = my_rank * (num_steps / num_cpus); i < (int)(num_steps /num_cpus); i++){
		if(i%2== 0)
			factor = 1.0;
		else factor = -1.0;
		sum1 += factor/(2.0 * i + 1.0);
	}

	//printf("sum1 = %ld\n",sum1);	
	MPI_Reduce(&sum1, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	
	/* Print the result */
	if (my_rank == 0) {
	
	pi = 4.0 * sum;
	double total = MPI_Wtime() - start;
	
	printf("%d, %ld, %lf, %.10lf\n", num_cpus, num_steps, total, pi);
	}
	MPI_Finalize();
	return 0;
}
