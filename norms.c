#include <stdio.h>
#include "config.h"
#include "norm.h"
#include "matrix.h"
#include "experiment.h"
#include "laplacian.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];


int main(int argc, char *argv[]) {
	printf("n,normf,normd\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);
		solve_naive(b, x, n);
		residual(actionf, b, x, r, n);

		printf("%d,", n);
		printf("%e,", normf(r,n));
		printf("%e\n", normd(r,n));
	}


	return 0;
}


// The results of normf and normd are practically the same
