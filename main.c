#include <stdio.h>
#include <math.h>
#include "config.h"
#include "matrix.h"


void residual(const Real b[], const Real x[], Real r[], int n) {
	action(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void error(const Real xe[], const Real x[], Real e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


double norm(const Real x[], int n) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrt(sum);
}


void setup(Real xe[], Real b[], int n) {
	for (int i = 0; i < n; ++i) {
		xe[i] = 1.0;
	}

	action(xe, b, n);
}


Real xe[NMAX];
Real x[NMAX];
Real b[NMAX];
Real r[NMAX];
Real e[NMAX];
Real d[NMAX];


int main() {
	printf("n,residual,error\n");


	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		solve(b, x, n);
		residual(b, x, r, n);
		error(xe, x, e, n);

		printf("%d,%e,%e\n", n, norm(r,n), norm(e,n));
	}


	return 0;
}
