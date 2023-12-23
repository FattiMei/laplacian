#include <math.h>
#include <stdio.h>
#include "matrix.h"


#ifndef NMAX
#define NMAX 10000
#endif


void residual(const float b[], const float x[], float r[], int n) {
	action(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void error(const float xe[], const float x[], float e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


double norm(const float x[], int n) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrt(sum);
}


void setup(float xe[], float b[], int n) {
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

	return 0;
}
