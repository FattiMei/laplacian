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
	printf("n,actionf,actiond,actionf_reordered\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);
		solve(b, x, n);

		printf("%d,", n);

		residual(actionf, b, x, r, n);
		printf("%e,", normd(r,n));

		residual(actiond, b, x, r, n);
		printf("%e,", normd(r,n));

		residual(actionf_reordered, b, x, r, n);
		printf("%e,", normd(r,n));

		residual(actiond_reordered, b, x, r, n);
		printf("%e\n", normd(r,n));
	}


	return 0;
}