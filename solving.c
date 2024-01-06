#include <stdio.h>
#include "config.h"
#include "experiment.h"
#include "laplacian.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float e[NMAX];


int main(int argc, char *argv[]) {
	printf("n,solve_naive,solve_better,solve_upper,solve_upper_rescaled,solve_upper_better\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);

		printf("%d,", n);

		solve_naive(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		solve_better(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		solve_upper(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		solve_upper_rescaled(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		solve_upper_better(b, x, n);
		error(xe, x, e, n);
		printf("%e\n", norm(e,n));
	}


	return 0;
}
