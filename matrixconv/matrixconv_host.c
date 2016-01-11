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

////////////////////////////////////////////////////////////////////////////////
#define WA 512
#define HA 512
#define WB 3
#define HB 3
#define WC 512
#define HC 512
////////////////////////////////////////////////////////////////////////////////

 
// Allocates a matrix with random float entries.
void randomMemInit(float* data, int size)
{
   int i;

   for (i = 0; i < size; ++i)
   	data[i] = rand() / (float)RAND_MAX;
}

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
	printf("cl:main program:matrixconv\n");
	
	cl_event event;

	long long ptimer1 = 0;
        long long ptimer2 = 0;
	long long ptotal_start = 0;
	long long ptotal_end = 0;

   int err;                            // error code returned from api calls

   cl_device_id device_id;             // compute device id 
   cl_context context;                 // compute context
   cl_command_queue commands;          // compute command queue
   cl_program program;                 // compute program
   cl_kernel kernel;                   // compute kernel

    // OpenCL device memory for matrices
   cl_mem d_A;
   cl_mem d_B;
   cl_mem d_C;

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
  
   printf("Initializing OpenCL device...\n"); 

   cl_uint dev_cnt = 0;
   clGetPlatformIDs(0, 0, &dev_cnt);
	
   cl_platform_id platform_ids[100];
  
   printf("cl:main program:Init_Device \n");
   
   ptotal_start = PAPI_get_virt_usec();
   ptimer1 = PAPI_get_virt_usec();
   clGetPlatformIDs(dev_cnt, platform_ids, NULL);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clGetPlatformIDs %llu us\n",(ptimer2-ptimer1));

	
   // Connect to a compute device
   int gpu = 1;
   ptimer1 = PAPI_get_virt_usec();
   err = clGetDeviceIDs(platform_ids[0], CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clGetDeviceIDs %llu us\n",(ptimer2-ptimer1));

   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to create a device group!\n");
       return EXIT_FAILURE;
   }
  
   ptimer1 = PAPI_get_virt_usec();
   // Create a compute context 
   context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clCreateContext %llu us\n",(ptimer2-ptimer1));

   if (!context)
   {
       printf("Error: Failed to create a compute context!\n");
       return EXIT_FAILURE;
   }

    ptimer1 = PAPI_get_virt_usec();
   // Create a command commands
   commands = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &err);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clCreateCommandQueue %llu us\n",(ptimer2-ptimer1));

if (!commands)
   {
       printf("Error: Failed to create a command commands!\n");
       return EXIT_FAILURE;
   }

   // Create the compute program from the source file
   char *KernelSource;
   long lFileSize;

   lFileSize = LoadOpenCLKernel("matrixconv_kernel.cl", &KernelSource);
   if( lFileSize < 0L ) {
       perror("File read failed");
       return 1;
   }

   ptimer1 = PAPI_get_virt_usec();
   /*Create program from source*/
   program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clCreateProgramWithSource %llu us\n",(ptimer2-ptimer1));

   if (!program)
   {
       printf("Error: Failed to create compute program!\n");
       return EXIT_FAILURE;
   }

   ptimer1 = PAPI_get_virt_usec();
   // Build the program executable
   err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clBuildProgram %llu us\n",(ptimer2-ptimer1));

   if (err != CL_SUCCESS)
   {
       size_t len;
       char buffer[2048];
       printf("Error: Failed to build program executable!\n");
       clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
       printf("%s\n", buffer);
       exit(1);
   }

    ptimer1 = PAPI_get_virt_usec();
   // Create the compute kernel in the program we wish to run
   kernel = clCreateKernel(program, "matrixconv", &err);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clCreateKernel %llu us\n",(ptimer2-ptimer1));

   if (!kernel || err != CL_SUCCESS)
   {
       printf("Error: Failed to create compute kernel!\n");
       exit(1);
   }

    ptimer1 = PAPI_get_virt_usec();
   // Create the input and output arrays in device memory for our calculation
   d_C = clCreateBuffer(context, CL_MEM_READ_WRITE, mem_size_A, NULL, &err);
   d_A = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size_A, h_A, &err);
   d_B = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size_B, h_B, &err);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clCreateBuffer %llu us\n",(ptimer2-ptimer1));


   if (!d_A || !d_B || !d_C)
   {
       printf("Error: Failed to allocate device memory!\n");
       exit(1);
   }    
    
   printf("Running matrix convolution for matrices A (%dx%d) and B (%dx%d) ...\n", WA,HA,WB,HB); 

   //Launch OpenCL kernel
   size_t localWorkSize[2], globalWorkSize[2];
 
   int wA = WA;
   int wB = WB;
   int wC = WC;
   ptimer1 = PAPI_get_virt_usec();
   err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&d_A);
   err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&d_B);
   err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&d_C);
   err |= clSetKernelArg(kernel, 3, sizeof(int), (void *)&wA);
   err |= clSetKernelArg(kernel, 4, sizeof(int), (void *)&wB);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clSetKernelArg %llu us\n",(ptimer2-ptimer1));


   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to set kernel arguments! %d\n", err);
       exit(1);
   }
 
   localWorkSize[0] = 16;
   localWorkSize[1] = 16;
   globalWorkSize[0] = WA;
   globalWorkSize[1] = HA;

   ptimer1 = PAPI_get_virt_usec();
   /*Enqueue task for parallelexecution*/
   err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, &event);
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clEnqueueNDRangeKernel %llu us\n",(ptimer2-ptimer1));


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
        printf("cl:main timing:opencl clEnqueueNDRangeKernel %0.3f us \n", total_time / 1000.0);

   ptimer1 = PAPI_get_virt_usec();
   //Retrieve result from device
   err = clEnqueueReadBuffer(commands, d_C, CL_TRUE, 0, mem_size_C, h_C, 0, NULL, NULL);
   ptotal_end = PAPI_get_virt_usec();
   ptimer2 = PAPI_get_virt_usec();
   printf("cl:main timing:PAPI clEnqueueReadBuffer %lluus\n",(ptimer2-ptimer1));

   printf("cl:main timing:PAPI total_time %llu us\n",(ptotal_end-ptotal_start));


   if (err != CL_SUCCESS)
   {
       printf("Error: Failed to read output array! %d\n", err);
       exit(1);
   }
 
   //print out the results
/*
   printf("\n\nMatrix C (Results)\n");
   int i;
   for(i = 0; i < size_C; i++)
   {
      printf("%f ", h_C[i]);
      if(((i + 1) % WC) == 0)
      printf("\n");
   }
   printf("\n");
*/
  
   printf("Matrix convolution completed...\n"); 

   //Shutdown and cleanup
   free(h_A);
   free(h_B);
   free(h_C);
 
   clReleaseMemObject(d_A);
   clReleaseMemObject(d_C);
   clReleaseMemObject(d_B);

   clReleaseProgram(program);
   clReleaseKernel(kernel);
   clReleaseCommandQueue(commands);
   clReleaseContext(context);

   return 0;
}
