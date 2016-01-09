pocl:transpose.c
	gcc -I/usr/local/include transpose.c -o transpose -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./transpose > test.txt
	echo 'OpenCL_API,Timing' > ../reports/transpose.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/transpose.csv
	rm -rf test.txt

linux64:transpose.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o transpose transpose.c -lOpenCL /usr/local/lib/libpapi.a
	./transpose

clean:
	rm -rf transpose output.pgm
