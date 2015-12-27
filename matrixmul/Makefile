hello:matrixmul_host.c
	gcc -I/usr/local/include matrixmul_host.c -o matrixmul_host -lm -lOpenCL /root/Documents/pocl/pocl-0.9/lib/poclu/.libs/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /root/Documents/PAPI/papi-5.4.1/src/libpapi.a

clean:
	rm -rf matrixmul_host
