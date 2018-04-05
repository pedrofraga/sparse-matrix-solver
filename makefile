.PHONY: tests

all:
	nvcc -O3 -std=c++11 -Xcompiler -fopenmp -D_MWAITXINTRIN_H_INCLUDED -D_FORCE_INLINES -D__STRICT_ANSI__ src/main.cpp src/*/*.cpp src/methods/cuda.cu -o bin/solver
memcheck:
	valgrind --tool=memcheck --leak-check=full -v bin/solver matrices/adder_dcop_32.mtx matrices/amazon0302.mtx
tests:
	nvcc -std=c++11 -Xcompiler -fopenmp,-g -D_MWAITXINTRIN_H_INCLUDED -D_FORCE_INLINES -D__STRICT_ANSI__ tests/*.cpp src/*/*.cpp src/methods/cuda.cu -o bin/tests
run-tests:
	./bin/tests
run:
	rm -f outputs/*.csv
	bin/solver matrices/cage4.mtx
runall:
	rm -f outputs/*.csv
	bin/solver $(wildcard matrices/*.mtx)

