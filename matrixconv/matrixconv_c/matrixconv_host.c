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
#define WA 1024 
#define HA 768
#define WB 3
#define HB 3
#define WC 1024
#define HC 768
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
        cl_event event;
        long long timer2 = 0;


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
  
   	printf("c:main program:log Matrix_A(%dx%d),Matrix_B(%dx%d)\n", WA,HA,WB,HB); 
	
	timer1 = PAPI_get_virt_usec();

	int x,y,r,c;
	for( x=0; x<WA ; x++)	
	{
		for(y=0; y<HA; y++)
		{
		    uint sum = 0;
		    for ( r = 0; r < WB; r++)
		    {
		         int tmp = (y + r) * WA + x;
		
		        for (c = 0; c < WB; c++)
		        {
	                        sum += h_B[(r * WB)  + c] * h_A[tmp + c];
		        }
		    }
	            h_C[y * WA + x] = sum;
		}
	}

	timer2 = PAPI_get_virt_usec();
	printf("c:main timing:PAPI logic %llu us \n",(timer2-timer1));

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
  

   	//Shutdown and cleanup
   	free(h_A);
   	free(h_B);
   	free(h_C);
 	
   	return 0;
}
