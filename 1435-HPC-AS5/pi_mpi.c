#include <mpi.h>
#include <stdio.h>
double MPI_Wtime ( );
int main(int argc, char **argv)
{
	long num_steps = atol(argv[1]);
	int my_rank, num_cpus, tag = 0, dest = 0, source;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_cpus);
	MPI_Status status;
	//printf("Hello, I am process %d among %d processes\n",my_rank, num_cpus);
	double a = 0, b = 1, step;
	double x, pi;
	step = 1.0 / num_steps;
	int d =  num_steps / num_cpus;
	int i = 0;
	double sum1 = 0, sum = 0;
	double f = step*d * my_rank;
	double start = MPI_Wtime();
	for(i = 0; i < num_steps /num_cpus; i++){
		x =  f +( i + 0.5) * step;
		sum1 += 4.0 /(1 + x * x);
	}
	
	if (my_rank == 0) 
	{
		sum = sum1;
		for (source = 1; source < num_cpus; source++) {
			MPI_Recv(&sum1, 1, MPI_DOUBLE, source, tag,MPI_COMM_WORLD, &status);
			sum += sum1;
		}
	} 
	else {
		MPI_Send(&sum1, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
	}
	
	/* Print the result */
	if (my_rank == 0) {
	printf("Time taken is : %lf\n", MPI_Wtime() - start);
	pi = sum * step;
	printf("With n = %d trapezoids, our estimate\n",num_steps);
	printf("of the integral(pi) from %lf to %lf = %lf\n",a, b, pi);
	}
	MPI_Finalize();
	return 0;
}
