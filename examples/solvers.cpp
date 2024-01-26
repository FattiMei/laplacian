#include <stdio.h>
#include <random>
#include "norm.h"
#include "laplacian.h"


#ifndef NMAX
#define NMAX 10000
#endif


#ifndef REAL
#define REAL float
#endif


REAL xe[NMAX];
REAL x[NMAX];
REAL b[NMAX];
REAL r[NMAX];
REAL e[NMAX];
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


void error(REAL xe[], REAL x[], REAL e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


int main(int argc, char *argv[]) {
	printf("n,thomas(fp32),thomas(fp64),multifrontal(fp32),multifrontal(fp64)\n");

	setup(xe, b, NMAX);

	for (int n = 10; n <= NMAX; ++n) {
		printf("%d,", n);
		action<REAL>(xe, b, n);

		thomas<float>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		thomas<double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		multifrontal<float>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		multifrontal<double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e\n", norm<double>(e,n));
	}


	return 0;
}
