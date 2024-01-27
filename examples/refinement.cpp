#include <stdio.h>
#include "norm.h"
#include "laplacian.h"


#ifndef NMAX
#define NMAX 10000
#endif


#ifndef ITMAX
#define ITMAX 100
#endif


#ifndef REAL
#define REAL float
#endif


REAL xe[NMAX];
REAL x[NMAX];
REAL b[NMAX];
REAL r[NMAX];
REAL diag[NMAX];


void setup(REAL xe[], REAL b[], int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<REAL> distribution(-1.0, 1.0);

	for (int i = 0; i < n; ++i) {
		xe[i] = distribution(gen);
	}

	action<REAL>(xe, b, n);
}


void residual(const REAL b[], const REAL x[], REAL r[], int n) {
	// the whole point of iterative refinement is computing a very precise correction
	action<double>(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


int main(int argc, char *argv[]) {
	setup(xe, b, NMAX);
	thomas<REAL>(b, diag, x, NMAX);


	printf("n,residual\n");

	REAL residual_norm;
	int it = 0;

	do {
		residual(b, x, r, NMAX);
		residual_norm = norm<REAL>(r, NMAX);

		thomas<REAL>(r, diag, correction, NMAX);

		for (int i = 0; i < NMAX; ++i) {
			x[i] += correction[i];
		}

		++it;
	} while (it < ITMAX && residual_norm < 1e-06);


	return 0;
}
