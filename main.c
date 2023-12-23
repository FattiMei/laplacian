#include <math.h>
#include <stdio.h>
#include "matrix.h"


#ifndef NMAX
#define NMAX 10000
#endif


void residual(int n, const float b[], const float x[], float r[]) {
	action(n, x, r);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void error(int n, const float xe[], const float x[], float e[]) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


double norm(int n, const float x[]) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrt(sum);
}


void setup(int n, float xe[], float b[]) {
	for (int i = 0; i < n; ++i) {
		xe[i] = 1.0;
	}

	action(n, xe, b);
}


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float e[NMAX];
float d[NMAX];


int main() {
	printf("n,residual,error\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(n, xe, b);
		solve(n, b, x, d);
		residual(n, b, x, r);
		error(n, xe, x, e);

		printf("%d,%e,%e\n", n, norm(n, r), norm(n, e));
	}

	return 0;
}
