pocl:matrixconv_host.c
	gcc -I/usr/local/include matrixconv_host.c -o matrixconv_host -lm -lOpenCL /usr/local/pocl/lib/libpoclu.so -Wl,-rpath -Wl,/usr/local/pocl/lib -O3 /usr/local/lib/libpapi.a
	./matrixconv_host > test.txt
	@if [ "$(shell uname -p)" = "x86_64" ]; \
		then \
			echo 'OpenCL_API,Timing' > ../reports/x86_64/matrixconv_host.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/x86_64/matrixconv_host.csv; \
			rm -rf test.txt; \
	elif [ "$(shell uname -p)" = "armv7l" ]; \
		then \
			echo 'OpenCL_API,Timing' > ../reports/armv7l/matrixconv_host.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../reports/armv7l/matrixconv_host.csv; \
			rm -rf test.txt; \
	else \
		echo "done"; \
	fi

linux64:matrixconv_host.c
	gcc -Wall -W -O2 -I/usr/include/ -L/usr/lib64/ -Wl,-rpath,/usr/lib64/ -o matrixconv_host matrixconv_host.c -lOpenCL /usr/local/lib/libpapi.a
	./matrixconv_host

clean:
	rm -rf matrixconv_host
