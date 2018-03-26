#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <omp.h>
#include "../utils/utils.h"

class Matrix {
	int cols, rows, nz;
	long long mflops;
	double start, done;
	double elapsed_time, measures;
	bool measuring;
public:
	double * x, * y;
	Matrix(int cols, int rows, int nz);
	double * getX();
	unsigned long long getGigaFlops();
	int getnz();
	int getCols();
	void printElapsedTime();
	void trackTime();
	void resetResults();
};

#endif
