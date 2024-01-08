#include <stdio.h>
#include "config.h"
#include "experiment.h"
#include "laplacian.h"
#include "../implementations/norm.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];


int main(int argc, char *argv[]) {
	printf("n,norm(fp32),norm(fp64)\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);
		solve(b, x, n);
		residual(actionf, b, x, r, n);

		printf("%d,%e,%e\n", n, norm<float>(r,n), norm<double>(r,n));
	}


	return 0;
}


// The results of normf and normd are practically the same
