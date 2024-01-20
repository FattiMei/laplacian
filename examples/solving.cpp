#include <stdio.h>
#include <random>
#include "norm.h"
#include "laplacian.h"


#define NMAX 10000


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float e[NMAX];
float diag[NMAX];


void setup(float xe[], float b[], int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	for (int i = 0; i < n; ++i) {
		xe[i] = distribution(gen);
	}

	action<double>(xe, b, n);
}


void error(float xe[], float x[], float e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


int main(int argc, char *argv[]) {
	printf("n,thomas(fp32),thomas(fp64),storeless(fp32),storeless(fp64)\n");

	setup(xe, b, NMAX);

	for (int n = 10; n <= NMAX; ++n) {
		printf("%d,", n);
		action<double>(xe, b, n);

		thomas<float>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		thomas<double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		storeless<float>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e,", norm<double>(e,n));

		storeless<double>(b, diag, x, n);
		error(xe, x, e, n);
		printf("%e\n", norm<double>(e,n));
	}


	return 0;
}
