pocl_profiling:
	cd gaussian_blur && $(MAKE) pocl
	cd linear_trnsfrm && $(MAKE) pocl
	cd log_transform && $(MAKE) pocl
	cd matrixconv && $(MAKE) pocl
	cd matrixmul && $(MAKE) pocl
	cd negative && $(MAKE) pocl
	cd power_law_trnsfrm && $(MAKE) pocl
	cd transpose && $(MAKE) pocl
	cd reports && ./append.py

linux64_profiling:
	cd gaussian_blur && $(MAKE) linux64
	cd linear_trnsfrm && $(MAKE) linux64
	cd log_transform && $(MAKE) linux64
	cd matrixconv && $(MAKE) linux64
	cd matrixmul && $(MAKE) linux64
	cd negative && $(MAKE) linux64
	cd power_law_trnsfrm && $(MAKE) linux64
	cd transpose && $(MAKE) linux64

clean:
	cd devquery && $(MAKE) clean
	cd hello && $(MAKE) clean
	cd gaussian_blur && $(MAKE) clean
	cd linear_trnsfrm && $(MAKE) clean
	cd log_transform && $(MAKE) clean
	cd matrixconv && $(MAKE) clean
	cd matrixmul && $(MAKE) clean
	cd negative && $(MAKE) clean
	cd power_law_trnsfrm && $(MAKE) clean
	cd transpose && $(MAKE) clean
	rm -rf reports/*.csv
	#rm -rf reports/*.xls

