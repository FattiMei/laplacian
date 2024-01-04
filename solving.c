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
	printf("n,solve_naive,solve_better,solve_upper\n");

	for (int n = 10; n <= NMAX; ++n) {
		printf("%d,", n);

		setup(actionf, xe, b, n);
		solve_naive(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e,", normd(r,n));

		setup(actionf, xe, b, n);
		solve_better(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e,", normd(r,n));

		setup(actionf, xe, b, n);
		solve_upper(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e\n", normd(r,n));

	}


	return 0;
}
