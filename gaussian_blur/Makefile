hello:gaussianblur_host.c
	gcc -I/usr/local/include gaussianblur_host.c -o gaussianblur_host -lm -lOpenCL /root/Documents/pocl/pocl-0.9/lib/poclu/.libs/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /root/Documents/PAPI/papi-5.4.1/src/libpapi.a

clean:
	rm -rf gaussianblur_host
	rm -rf output.pgm
