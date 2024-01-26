#include <stdio.h>
#include "laplacian.h"
#include "norm.h"


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
	for (int i = 0; i < n; ++i) {
		xe[i] = static_cast<REAL>(1.0);
	}

	action<REAL>(xe, b, n);
}


void residual(const REAL b[], const REAL x[], REAL r[], int n) {
	action<REAL>(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void bad_residual(const REAL b[], const REAL x[], REAL r[], int n) {
	bad_action<REAL>(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


int main() {
	printf("n,residual,bad_residual\n");


	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		thomas<REAL>(b, diag, x, n);

		printf("%d,", n);

		residual(b, x, r, n);
		printf("%e,", norm<REAL>(r,n));

		bad_residual(b, x, r, n);
		printf("%e\n", norm<REAL>(r,n));
	}


	return 0;
}
