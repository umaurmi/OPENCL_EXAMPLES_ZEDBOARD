pocl:logtrns.c
	gcc -I/usr/local/include logtrns.c -o logtrns -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./logtrns > test.txt
	@if [ "$(shell uname -p)" = "x86_64" ]; \
		then \
			echo 'OpenCL_API,Timing' > ../reports/x86_64/logtrns.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/x86_64/logtrns.csv; \
			rm -rf test.txt; \
	elif [ "$(shell uname -p)" = "armv7l" ]; \
		then \
			echo 'OpenCL_API,Timing' > ../reports/armv7l/logtrns.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/armv7l/logtrns.csv; \
			rm -rf test.txt; \
	else \
		echo "done"; \
	fi

linux64:logtrns.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o logtrns logtrns.c -lOpenCL /usr/local/lib/libpapi.a
	./logtrns

clean:
	rm -rf logtrns output.pgm
