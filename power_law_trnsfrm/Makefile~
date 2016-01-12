pocl:power_law.c
	gcc -I/usr/local/include power_law.c -o power_law -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./power_law > test.txt
	echo 'OpenCL_API,Timing' > ../reports/power_law.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/power_law.csv
	rm -rf test.txt

linux64:power_law.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o power_law power_law.c -lOpenCL /usr/local/lib/libpapi.a
	./power_law

clean:
	rm -rf power_law output.pgm


