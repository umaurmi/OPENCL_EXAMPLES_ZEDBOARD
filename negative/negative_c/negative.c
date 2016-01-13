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
    
	int i, j, width, height;
	float *in_image;
	float *out_image;

    	pgm_t ipgm;
    	pgm_t opgm;


	/* Image file input */
	readPGM(&ipgm, "lena.pgm");
	printf("c:main program:log read_img_done\n");

	width= ipgm.width;
	printf("c:main program:log img_width is %d \n", width);
	height = ipgm.height;
	printf("c:main program:log img_height is %d \n", height);

	in_image = (float *)malloc(width * height * sizeof(float));
	out_image = (float *)malloc(width * height * sizeof(float));

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			((float*)in_image)[(width*j) + i] = (float)ipgm.buf[width*j + i];
		}
	}
	timer1 = PAPI_get_virt_usec();

 	for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {

                        ((float*)out_image)[(width*j) + i] = 255-(((float*)in_image)[(width*j) + i]);
                }
        }

	 timer2 = PAPI_get_virt_usec();
	 printf("c:main timing:PAPI logic %llu us\n",(timer2-timer1));
	

	opgm.width = width;
	opgm.height = height;
	normalizeF2PGM(&opgm, out_image);

	/* Image file output */
	writePGM(&opgm, "output.pgm");

	printf("c:main program:log output_done\n");

	destroyPGM(&ipgm);
	destroyPGM(&opgm);

	free(in_image);
	free(out_image);

	return 0;
}
