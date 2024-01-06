#include <stdio.h>
#include "config.h"
#include "experiment.h"
#include "laplacian.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float e[NMAX];


int main(int argc, char *argv[]) {
	printf("n,solve_naive,solvef,solved,multifrontal\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);

		printf("%d,", n);

		solve_naive(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e,", norm(r,n));

		solvef(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e,", norm(r,n));

		solved(b, x, n);
		residual(actionf, b, x, r, n);
		printf("%e,", norm(r,n));

		multifrontal(b, x, n);
		printf("%e\n", norm(r,n));
	}


	return 0;
}
