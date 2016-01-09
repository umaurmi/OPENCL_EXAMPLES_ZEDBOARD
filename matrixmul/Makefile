pocl:matrixmul_host.c
	gcc -I/usr/local/include matrixmul_host.c -o matrixmul_host -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./matrixmul_host > test.txt
	echo 'OpenCL_API,Timing' > ../reports/matrixmul_host.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/matrixmul_host.csv
	rm -rf test.txt

linux64:matrixmul_host.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o matrixmul_host matrixmul_host.c -lOpenCL /usr/local/lib/libpapi.a
	./matrixmul_host

clean:
	rm -rf matrixmul_host
