#include <stdio.h>
#include "norm.h"
#include "laplacian.h"


#define NMAX 100


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float diag[NMAX];


void setup(float xe[], float b[], int n) {
	for (int i = 0; i < n; ++i) {
		xe[i] = 1.0;
	}

	action<double>(xe, b, n);
}


void residual(const float b[], const float x[], float r[], int n) {
	action<double>(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


int main(int argc, char *argv[]) {
	printf("n,norm(fp32),norm(fp64)\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		thomas<float>(b, diag, x, n);
		residual(b, x, r, n);

		printf("%d,%e,%e\n", n, norm<float>(r,n), norm<double>(r,n));
	}


	return 0;
}


// The results of normf and normd are practically the same
