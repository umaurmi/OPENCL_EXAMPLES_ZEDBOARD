pocl:negative.c
	gcc -I/usr/local/include negative.c -o negative -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./negative > test.txt
	echo 'OpenCL_API,Timing' > ../reports/negative.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/negative.csv
	rm -rf test.txt

linux64:negative.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o negative negative.c -lOpenCL /usr/local/lib/libpapi.a
	./negative

clean:
	rm -rf negative output.pgm
