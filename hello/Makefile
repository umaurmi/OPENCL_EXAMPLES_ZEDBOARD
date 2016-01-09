pocl:hello.c
	gcc -I/usr/local/include hello.c -o hello -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a

linux64:hello.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o hello hello.c -lOpenCL /usr/local/lib/libpapi.a

clean:
	rm -rf hello
