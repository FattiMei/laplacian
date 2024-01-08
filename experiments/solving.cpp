#include <stdio.h>
#include "norm.h"
#include "laplacian.h"


#define NMAX 10000


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float e[NMAX];
float diag[NMAX];


void setup(float xe[], float b[], int n) {
	for (int i = 0; i < n; ++i) {
		xe[i] = 1.0;
	}

	action<double>(xe, b, n);
}


void error(float xe[], float x[], float e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


int main(int argc, char *argv[]) {
	// @TODO: aggiungere anche metodo multifrontale
	printf("n,thomas(fp32),thomas(fp64),thomas(fp80)\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);

		printf("%d,", n);

		thomas<float>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		thomas<double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		thomas<long double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e\n", norm<double>(e,n));
	}


	return 0;
}
