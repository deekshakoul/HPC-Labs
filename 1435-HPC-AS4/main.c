
#include<stdio.h>
#include<math.h>
#include "omp.h"

int main(int argc, char **argv){
	
	if(argc < 4){
		printf("Usage : %s <input_image> <output_image> <num_threads>\n",argv[0]);
		return 1;
	}
	int threads = atoi(argv[3]);
	short **array, **array1;
	long height = 0, width = 0, i, j;
	//PARALLEL CODE
	array = read_bmp_image(argv[1], &height, &width);
	array1 = warp_image_parallel(array, height, width, threads);
	create_bmp_file_if_needed(argv[1], argv[2], array1);
	write_bmp_image(argv[2], array1);
	free_image_array(array, height);
	free_image_array(array1, height);

	//SERIAL CODE	
	array = read_bmp_image(argv[1], &height, &width);
	array1 = warp_image_serial(array, height, width, threads);
	create_bmp_file_if_needed(argv[1], argv[2], array1);
	write_bmp_image(argv[2], array1);
	free_image_array(array, height);
	free_image_array(array1, height);

	return 0;
}
