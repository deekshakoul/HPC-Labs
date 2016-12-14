#include <stdio.h>
#include <omp.h>

int main (int argc, char **argv){
	double time = omp_get_wtime();
	int n = atoi(argv[1]);
	int THREADS = atoi(argv[2]);
	double factor = 1.0;
	double sum = 0.0, pi;
	int i;
	#pragma omp parallel for num_threads(THREADS) private(factor) reduction(+ : sum)
	for(i = 0; i < n; i++){
		if(i % 2 == 0) factor = 1;
		else factor = -1;
		sum += factor/(2 * i + 1);
	}
	pi = 4 * sum;
	
	printf("%d, %d, %lf, %.10lf\n", THREADS, n, omp_get_wtime() - time, pi);
	return 0;
}

