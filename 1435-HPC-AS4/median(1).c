#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include"omp.h"
double time;
// compare function for quicksort
int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

// half width = 3

// function to find median value for each pixel in the image
int getMedian(char** arr, int h, int w, int x, int y) {
    int nBors[8] = {0}; // array to store all the neighbor values of the cell
    
    // copy all neighbor values into the nBors array consideringboundary conditions
    if(x > 0 && y > 0) {
        nBors[0] = arr[x-1][y-1];
        if(y < h-1)
            nBors[2] = arr[x-1][y+1];
    }
    if(x > 0)
        nBors[1] = arr[x-1][y];
    if(y > 0)
        nBors[3] = arr[x][y-1];
    if(y < h-1)
        nBors[4] = arr[x][y+1];
    if(x > 0 && x < h-1 && y > 0) {
        nBors[5] = arr[x+1][y-1];
        nBors[6] = arr[x+1][y];
        if(y < h-1)
            nBors[7] = arr[x+1][y+1];
    }
    
    // sort all neighbor values
    qsort(nBors, 8, sizeof(int), cmpfunc);
    
    // return the median value that can replace the original value of the cell
    return nBors[4];
}

// function to apply median filter on input image

void median(char* input,char* output,int threads) {
    FILE* f = fopen(input,"rb"); // open input bmp file in read binary mode
    FILE* fp = fopen(output,"wb"); // open output bmp file in write binary mode
    int i = 0, size = 0, h, w; // h - height of image, w - width of image
    if(f == NULL) {
        printf("could not open file\n");
        return;
    } else if(fp == NULL) {
        printf("could not write to file\n");
        return;
    } else { // if both files have been openeed correctly, apply median filter to input image
        fseek(f,18,SEEK_SET); // read height of image from bmp header
        fread(&h,sizeof(int),1,f);
        fseek(f,22,SEEK_SET); // read width of image from bmp header
        fread(&w,sizeof(int),1,f);
        fseek(f,34,SEEK_SET); // read size of image from bmp header
        fread(&size,sizeof(int),1,f);
        fseek(f,0,SEEK_SET); // reset file pointer to the beginning of the image
        char c; // temp variable to hold the ASCII value before writing to image matrix or output image
        
        // read the header from the input image and copy it as is into the output image
        while(i < 54) {
            fread(&c, sizeof(char),1,f);
            fwrite(&c,sizeof(char),1,fp);
            i++;
        }
        
        // read the rest of the bmp file - image data one value at a time, apply median filter and write to output image
        
            int j,k;
            char **arr = (char **)malloc(h * sizeof(char *));
            for (i=0; i<h; i++)
                arr[i] = (char *)malloc(w * sizeof(char));
            for(j=0;j<h;j++) {
                for(k=0;k<w;k++) {
                    fread(&c, sizeof(char),1,f);
                    arr[j][k] = c;
                    int temp = atoi(&arr[j][k]);
                    	
                }
            }
            int index, xp, yp, tx = w/2, ty = h/2;
			#pragma omp omp_num_threads(threads) parallel for private(yp,xp,c) shared(h,w,fp,arr) schedule(dynamic,tx)
            for(yp=0;yp<h;yp++) {
                for(xp=0;xp<w;xp++) {
                    c = (char)getMedian(arr,h,w,yp,xp);
                    fwrite(&c,sizeof(char),1,fp);	
                }
            }
            
        printf("\nTIME FOR MEDIAN FILTER IS %lf\n",omp_get_wtime()-time);
        
        // close all open files
        fclose(f);
        fclose(fp);
    }

    return;	
}

int main(int *argc, char* argv[]){
	if(!argv[2] || !argv[3]){
		printf("usage: ./a.out no_of_threads input_file output_file\n");
	 time = omp_get_wtime();
	median(argv[2],argv[3],atoi(argv[1]));
	
	return 0;
}
}
