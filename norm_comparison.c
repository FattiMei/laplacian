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
	printf("n,normf,normd\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		solve(b, x, n);
		residual(b, x, r, n);

		printf(
			  "%d,%e,%e\n"
			, n
			, norm(r,n)
			, norm(r,n)
		);
	}


	return 0;
}
