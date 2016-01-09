pocl:linear_trnsfrm.c
	gcc -I/usr/local/include linear_trnsfrm.c -o linear_trnsfrm -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./linear_trnsfrm > test.txt 
	echo 'OpenCL_API,Timing' > ../reports/linear_trnsfrm.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/linear_trnsfrm.csv
	rm -rf test.txt

linux64:linear_trnsfrm.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o linear_trnsfrm linear_trnsfrm.c -lOpenCL /usr/local/lib/libpapi.a
	./linear_trnsfrm

clean:
	rm -rf linear_trnsfrm output.pgm
