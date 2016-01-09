pocl:devquery.c
	gcc -I/usr/local/include devquery.c -o devquery -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./devquery

linux64:devquery.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o devquery devquery.c -lOpenCL /usr/local/lib/libpapi.a
	./devquery

clean:
	rm -rf devquery
