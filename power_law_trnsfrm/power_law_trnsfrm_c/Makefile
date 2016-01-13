c:power_law.c
	gcc -I/usr/local/include power_law.c -o power_law -lm -O3 /usr/local/lib/libpapi.a
	./power_law > test.txt
	@if [ "$(shell uname -p)" = "x86_64" ]; \
		then \
			echo 'c_Logic,Timing' > ../../reports/x86_64_c/power_law.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../../reports/x86_64_c/power_law.csv; \
			rm -rf test.txt; \
	elif [ "$(shell uname -p)" = "armv7l" ]; \
		then \
			echo 'C_Logic,Timing' > ../../reports/armv7l_c/power_law.csv; \
			sed -n '/PAPI/p' test.txt | awk '{print $$3,$$4}' OFS="," >> ../../reports/armv7l_c/power_law.csv; \
			rm -rf test.txt; \
	else \
		echo "done"; \
	fi


clean:
	rm -rf power_law output.pgm *~
