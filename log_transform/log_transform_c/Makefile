c:logtrns.c
	gcc -I/usr/local/include logtrns.c -o logtrns -lm -O3 /usr/local/lib/libpapi.a
	./logtrns > test.txt
	@if [ "$(shell uname -p)" = "x86_64" ]; \
		then \
			echo 'c_Logic,Timing' > ../../reports/x86_64_c/logtrns.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../../reports/x86_64_c/logtrns.csv; \
			rm -rf test.txt; \
	elif [ "$(shell uname -p)" = "armv7l" ]; \
		then \
			echo 'C_Logic,Timing' > ../../reports/armv7l_c/logtrns.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../../reports/armv7l_c/logtrns.csv; \
			rm -rf test.txt; \
	else \
		echo "done"; \
	fi

clean:
	rm -rf logtrns output.pgm *~

