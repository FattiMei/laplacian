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
REAL d[NMAX];


void setup(REAL xe[], REAL b[], int n) {
	for (int i = 0; i < n; ++i) {
		xe[i] = static_cast<REAL>(1.0);
	}

	action<double>(xe, b, n);
}


void residual(const REAL b[], const REAL x[], REAL r[], int n) {
	action<double>(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void error(const REAL xe[], const REAL x[], REAL e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


int main() {
	printf("n,residual,error\n");


	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		thomas<REAL>(b, x, n);
		residual(b, x, r, n);
		error(xe, x, e, n);

		printf("%d,%e,%e\n", n, norm<REAL>(r,n), norm<REAL>(e,n));
	}


	return 0;
}
