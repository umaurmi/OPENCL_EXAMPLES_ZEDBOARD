////////////////////////////////////////////////////////////////////////////////

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <CL/cl.h>
#include <stdbool.h>
#include "papi.h"

////////////////////////////////////////////////////////////////////////////////
#define WA 128
#define HA 128
#define WB 128

#define HB WA
#define WC WB
#define HC HA
////////////////////////////////////////////////////////////////////////////////

 
// Allocates a matrix with random float entries.
void randomMemInit(float* data, int size)
{
   int i;

   for (i = 0; i < size; ++i)
   	data[i] = i;
}

int main(int argc, char** argv)
{
	long long timer1 = 0;
        long long timer2 = 0;

   	// set seed for rand()
   	srand(2014);
 
   	//Allocate host memory for matrices A and B
   	unsigned int size_A = WA * HA;
   	unsigned int mem_size_A = sizeof(float) * size_A;
   	float* h_A = (float*) malloc(mem_size_A);
 	
 	unsigned int size_B = WB * HB;
 	unsigned int mem_size_B = sizeof(float) * size_B;
 	float* h_B = (float*) malloc(mem_size_B);
	
   	//Initialize host memory
   	randomMemInit(h_A, size_A);
   	randomMemInit(h_B, size_B);
 
   	//Allocate host memory for the result C
   	unsigned int size_C = WC * HC;
   	unsigned int mem_size_C = sizeof(float) * size_C;
   	float* h_C = (float*) malloc(mem_size_C);
  	
  	int tx,ty,k;
	
	timer1 = PAPI_get_virt_usec();
		
	for(tx =0; tx < HA; tx++)
	{
	   for(ty = 0; ty <WB; ty++)
	   { 
	   	h_C[ty * WA + tx] = 0;
	   	for (k = 0; k < WA; ++k)
	   	{
		   float elementA = h_A[ty * WA + k];
   		   float elementB = h_B[k * WB + tx];
   		   h_C[ty * WA + tx]+= elementA * elementB;
   		}
   	  }	
  	}	

  	timer2 = PAPI_get_virt_usec();
  	printf("c:main timing:PAPI logic %llu us\n",(timer2-timer1));
 	
 	#ifdef print
 	printf("\n\nMatrix A \n");
 	int i;
 	for(i = 0; i < size_A; i++)
 	{
 	     printf("%f ", h_A[i]);
 	     if(((i + 1) % WA) == 0)
 	     printf("\n");
 	}
 	printf("\n");
	
	printf("\n\nMatrix B\n");
	for(i = 0; i < size_B; i++)
	{
	      printf("%f ", h_B[i]);
	      if(((i + 1) % WB) == 0)
	      printf("\n");
	}
	printf("\n"); 
	
	//print out the results
	printf("\n\nMatrix C (Results)\n");
	for(i = 0; i < size_C; i++)
   	{
     	 	printf("%f ", h_C[i]);
     		if(((i + 1) % WC) == 0)
      		printf("\n");
   	}
   	printf("\n");
  	#endif

   	free(h_A);
   	free(h_B);
   	free(h_C);
 	
 	return 0;
}
