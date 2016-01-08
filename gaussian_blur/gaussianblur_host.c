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

#include "pgm.h"
#include "papi.h"

long LoadOpenCLKernel(char const* path, char **buf)
{
    FILE  *fp;
    size_t fsz;
    long   off_end;
    int    rc;

    /* Open the file */
    fp = fopen(path, "r");
    if( NULL == fp ) {
        return -1L;
    }

    /* Seek to the end of the file */
    rc = fseek(fp, 0L, SEEK_END);
    if( 0 != rc ) {
        return -1L;
    }

    /* Byte offset to the end of the file (size) */
    if( 0 > (off_end = ftell(fp)) ) {
        return -1L;
    }
    fsz = (size_t)off_end;

    /* Allocate a buffer to hold the whole file */
    *buf = (char *) malloc( fsz+1);
    if( NULL == *buf ) {
        return -1L;
    }

    /* Rewind file pointer to start of file */
    rewind(fp);

    /* Slurp file into buffer */
    if( fsz != fread(*buf, 1, fsz, fp) ) {
        free(*buf);
        return -1L;
    }

    /* Close the file */
    if( EOF == fclose(fp) ) {
        free(*buf);
        return -1L;
    }


    /* Make sure the buffer is NUL-terminated, just in case */
    (*buf)[fsz] = '\0';

    /* Return the file size */
    return (long)fsz;
}

int main(int argc, char** argv)
{
	cl_event event;

        long long ptimer1=0;
        long long ptimer2=0;

   int err;                            // error code returned from api calls
   int ipgm_img_width = 0;
   int ipgm_img_height = 0;
   int i = 0;
   int j = 0;
   pgm_t ipgm;
   pgm_t opgm;
   cl_device_id device_id;             // compute device id 
   cl_context context;                 // compute context
   cl_command_queue commands;          // compute command queue
   cl_program program;                 // compute program
   cl_kernel kernel;                   // compute kernel

    // OpenCL device memory for matrices
   cl_mem d_A;
   cl_mem d_B;
   cl_mem d_C;

   /* Image file input */
    readPGM(&ipgm,"sunny_uhd.pgm");

    ipgm_img_width = ipgm.width;
    ipgm_img_height = ipgm.height;
    printf("image width is %d \n", ipgm_img_width);
    printf("image height is %d \n", ipgm_img_height);
 
   //Allocate host memory for matrices A and B
   unsigned int size_A = ipgm_img_width*ipgm_img_height;
   unsigned int mem_size_A = sizeof(float) * size_A;
   float* h_A = (float*) malloc(mem_size_A);
   for(i = 0; i < ipgm_img_height; i++ ) {   //interchanged ht and width
        for(j = 0; j < ipgm_img_width; j++ ) {
                ((float*)h_A)[(ipgm_img_height*j) + (i)] = (float)ipgm.buf[(ipgm_img_height*j) + (i)];
        }
    }
 
   unsigned int size_B = 9;
   unsigned int mem_size_B = sizeof(float) * size_B;
   float* h_B = (float*) malloc(mem_size_B);
   h_B[0] = 1;
   h_B[1] = 1;
   h_B[2] = 1;
   h_B[3] = 1;
   h_B[4] = 1;
   h_B[5] = 1;
   h_B[6] = 1;
   h_B[7] = 1;
   h_B[8] = 1;
    

   //Allocate host memory for the result C
   unsigned int size_C = ipgm_img_width * ipgm_img_height;
   unsigned int mem_size_C = sizeof(float) * size_C;
   float* h_C = (float*) malloc(mem_size_C);
  
   printf("Initializing OpenCL device...\n"); 

   cl_uint dev_cnt = 0;
   clGetPlatformIDs(0, 0, &dev_cnt);
	
   cl_platform_id platform_ids[100];
   clGetPlatformIDs(dev_cnt, platform_ids, NULL);
	
   // Connect to a compute device
   int gpu = 1;
   err = clGetDeviceIDs(platform_ids[0], CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to create a device group!\n");
       return EXIT_FAILURE;
   }
  
   // Create a compute context 
   context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
   if (!context)
   {
       printf("Error: Failed to create a compute context!\n");
       return EXIT_FAILURE;
   }

   // Create a command commands
   commands = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &err);
   if (!commands)
   {
       printf("Error: Failed to create a command commands!\n");
       return EXIT_FAILURE;
   }

   // Create the compute program from the source file
   char *KernelSource;
   long lFileSize;

   lFileSize = LoadOpenCLKernel("gaussianblur_kernel.cl", &KernelSource);
   if( lFileSize < 0L ) {
       perror("File read failed");
       return 1;
   }

   program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
   if (!program)
   {
       printf("Error: Failed to create compute program!\n");
       return EXIT_FAILURE;
   }

   // Build the program executable
     err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
     //err = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);


   if (err != CL_SUCCESS)
   {
       size_t len;
       char buffer[2048];
       printf("Error: Failed to build program executable!\n");
       clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
       printf("%s\n", buffer);
       exit(1);
   }

   // Create the compute kernel in the program we wish to run
   //
   kernel = clCreateKernel(program, "gaussianblur", &err);
   if (!kernel || err != CL_SUCCESS)
   {
       printf("Error: Failed to create compute kernel!\n");
       exit(1);
   }

   // Create the input and output arrays in device memory for our calculation
   d_C = clCreateBuffer(context, CL_MEM_READ_WRITE, mem_size_A, NULL, &err);
   d_A = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size_A, h_A, &err);
   d_B = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size_B, h_B, &err);

   if (!d_A || !d_B || !d_C)
   {
       printf("Error: Failed to allocate device memory!\n");
       exit(1);
   }    
    
   printf("Running gaussian blur\n"); 

   //Launch OpenCL kernel
   size_t localWorkSize[2], globalWorkSize[2];
 
   int wA = ipgm_img_width;
   int wB = 3;
   int wC = ipgm_img_width;
   err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&d_A);
   err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&d_B);
   err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&d_C);
   err |= clSetKernelArg(kernel, 3, sizeof(int), (void *)&wA);
   err |= clSetKernelArg(kernel, 4, sizeof(int), (void *)&wB);

   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to set kernel arguments! %d\n", err);
       exit(1);
   }
 
   localWorkSize[0] = 4;
   localWorkSize[1] = 4;
   globalWorkSize[0] = ipgm_img_width;
   globalWorkSize[1] = ipgm_img_height;
 
 	ptimer1 = PAPI_get_virt_usec();

   /*Enqueue task for parallel execution*/
   err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, globalWorkSize, NULL, 0, NULL, &event);

 	ptimer2 = PAPI_get_virt_usec();
        printf("Time elapsed (using PAPI) is %llu us\n",(ptimer2-ptimer1));

   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to execute kernel! %d\n", err);
       exit(1);
   }
 
	//opencl timer
	clWaitForEvents(1, &event);
	clFinish(commands);
	cl_ulong time_start, time_end;
	double total_time;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
	total_time = time_end - time_start;
	printf("OpenCl Execution time is: %0.3f us \n", total_time / 1000.0);

   //Retrieve result from device
   err = clEnqueueReadBuffer(commands, d_C, CL_TRUE, 0, mem_size_C, h_C, 0, NULL, NULL);

   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to read output array! %d\n", err);
       exit(1);
   }
 
   /* Copy to buffer - not needed */
    float* ampd;
    ampd = (float*)malloc(ipgm_img_width*ipgm_img_height*sizeof(float));
    for (i=0; i<ipgm_img_height; i++) { //interchanged ht and width
        for (j=0; j<ipgm_img_width; j++) {
                        ampd[(ipgm_img_height*j) + (i)] = (((float*)h_C)[(ipgm_img_height*j) + (i)]);
        }
    }


   printf("Gaussian blur completed...\n"); 

   opgm.width = ipgm_img_width;
   opgm.height = ipgm_img_height;
   normalizeF2PGM(&opgm, ampd);

   /* Output image */
   writePGM(&opgm, "output.pgm");

   //Shutdown and cleanup
   free(h_A);
   free(h_B);
   free(h_C);
   free(ampd);

   destroyPGM(&ipgm);
   destroyPGM(&opgm);
 
   clReleaseMemObject(d_A);
   clReleaseMemObject(d_C);
   clReleaseMemObject(d_B);

   clReleaseProgram(program);
   clReleaseKernel(kernel);
   clReleaseCommandQueue(commands);
   clReleaseContext(context);

   return 0;
}
