/*Exclusive Prefix Sum Serial*/
/*Date : 6 Sep, 2015*/
#include <stdio.h>
#include "omp.h"

int main(int argc, char* argv[]){
	
	int input[8] = {3, 1, 7, 0, 4, 1, 6, 3};
	int result[8];
	int running_sum = 0;
	for(int i = 0; i < 8; ++i)
	{
		result[i] = running_sum;
		running_sum += input[i];
	}
}