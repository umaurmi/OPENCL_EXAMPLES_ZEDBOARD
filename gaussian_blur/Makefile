pocl:gaussianblur_host.c
	gcc -I/usr/local/include gaussianblur_host.c -o gaussianblur_host -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a

linux64:gaussianblur_host.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o gauss gaussianblur_host.c -lOpenCL /usr/local/lib/libpapi.a

clean:gaussianblur_host.c
	rm -rf gaussianblur_host output.pgm
