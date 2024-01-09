#include <stdio.h>
#include "norm.h"
#include "laplacian.h"




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


void error(float xe[], float x[], float e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


#define N 10000


float xe[N];
float x[N];
float b[N];
float r[N];
float correction[N];
float diag[N];


int main(int argc, char *argv[]) {
	setup(xe, b, N);
	thomas<float>(b, diag, x, N);


	printf("n,err\n");

	for (int it = 0; it < 100; ++it) {
		residual(b, x, r, N);
		printf("%d,%e\n", it, norm<float>(r,N));


		// refinement
		thomas<float>(r, diag, correction, N);

		for (int i = 0; i < N; ++i) {
			x[i] += correction[i];
		}
	}


	return 0;
}
