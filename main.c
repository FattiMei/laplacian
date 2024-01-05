#include <stdio.h>
#include "config.h"
#include "matrix.h"
#include "experiment.h"
#include "laplacian.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float e[NMAX];
float d[NMAX];


int main(int argc, char *argv[]) {
	printf("n,residual,error\n");


	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);
		solve_naive(b, x, n);
		residual(actionf, b, x, r, n);
		error(xe, x, e, n);

		printf("%d,%e,%e\n", n, norm(r,n), norm(e,n));
	}


	return 0;
}
