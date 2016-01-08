#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pgm.h"
#include "papi.h"

#define MAX_SOURCE_SIZE (0x100000)


int main()
{
  	long long timer1 = 0;
  	long long timer2 = 0;
    
	int i, j, n;
	float *in_image;
	float *out_image;

    	pgm_t ipgm;
    	pgm_t opgm;


	/* Image file input */
	readPGM(&ipgm, "lena.pgm");
	printf("reading image done ...");

	n = ipgm.width;
	printf("image width is %d \n", n);
	
	in_image = (float *)malloc(n * n * sizeof(float));
	out_image = (float *)malloc(n * n * sizeof(float));


	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {

			((float*)in_image)[(n*j) + i] = (float)ipgm.buf[n*j + i];
		}
	}

	timer1 = PAPI_get_virt_usec();

	for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {

                        ((float*)out_image)[(n*j) + i] = 255-(((float*)in_image)[(n*j) + i]);
                }
        }

	 timer2 = PAPI_get_virt_usec();
	 printf("Time elapsed is %llu us\n",(timer2-timer1));

	printf("computing negative done...\n");

	opgm.width = n;
	opgm.height = n;
	normalizeF2PGM(&opgm, out_image);

	/* Image file output */
	writePGM(&opgm, "output.pgm");

	printf("output pgm done ...\n");

	destroyPGM(&ipgm);
	destroyPGM(&opgm);

	free(in_image);
	free(out_image);

	return 0;
}
