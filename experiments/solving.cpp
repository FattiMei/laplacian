#include <stdio.h>
#include "config.h"
#include "experiment.h"
#include "norm.h"
#include "laplacian.h"


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float e[NMAX];


int main(int argc, char *argv[]) {
	// @TODO: aggiungere anche metodo multifrontale
	printf("n,thomas(fp32),thomas(fp64),thomas(fp80)\n");

	for (int n = 10; n <= NMAX; ++n) {
		setup(actionf, xe, b, n);

		printf("%d,", n);

		thomas<float>(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		thomas<double>(b, x, n);
		error(xe, x, e, n);
		printf("%e,", norm(e,n));

		thomas<long double>(b, x, n);
		error(xe, x, e, n);
		printf("%e\n", norm(e,n));
	}


	return 0;
}
