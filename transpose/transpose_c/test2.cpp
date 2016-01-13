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

	register int i,j;
	float *in_image;
	float *out_image;
	int width, height;
	
	pgm_t ipgm;
    	pgm_t opgm;


   	/* Image file input */
	readPGM(&ipgm, "test_img_old.pgm");
	printf("reading file done ... \n");

    	width = ipgm.width; 
	height = ipgm.height;
	printf("width of image is %d\n",width);
	printf("width of image is %d\n", height);

	in_image = (float *)malloc(width * height * sizeof(float));
	out_image = (float *)malloc(width * height * sizeof(float));

    	for( i = 0; i < width; i++ ) {
        	for( j = 0; j < height; j++ ) {

			((float*)in_image)[(width*j) + i] = (float)ipgm.buf[width*j + i];
        	}
    	}
	
	timer1 = PAPI_get_virt_usec();
	
 	for( i = 0; i < width; i++ ) {
                for( j = 0; j < height; j++ ) {
			((float*)out_image)[(height*i) + j] = ((float*)in_image)[(width*j) + i];
        	}	
    	 }

    	timer2 = PAPI_get_virt_usec();
    	printf("Time elapsed is %llu us\n",(timer2-timer1));
	
    	printf("computing transpose done...\n");

    	opgm.width = height ;
    	opgm.height = width ;
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
