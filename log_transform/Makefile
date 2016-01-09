pocl:logtrns.c
	gcc -I/usr/local/include logtrns.c -o logtrns -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./logtrns > test.txt
	echo 'OpenCL_API,Timing' > ../reports/logtrns.csv
	sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/logtrns.csv
	rm -rf test.txt

linux64:logtrns.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o logtrns logtrns.c -lOpenCL /usr/local/lib/libpapi.a
	./logtrns

clean:
	rm -rf logtrns output.pgm
