#include <stdio.h>
#include "config.h"
#include "norm.h"
#include "matrix.h"
#include "experiment.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];


int main(int argc, char *argv[]) {
	printf("n,normf,normd,normf_ordered\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(action, xe, b, n);
		solve(b, x, n);
		residual(action, b, x, r, n);

		printf("%d,", n);
		printf("%e,", normf(r,n));
		printf("%e,", normd(r,n));
		printf("%e\n", normf_ordered(r,n));
	}


	return 0;
}
