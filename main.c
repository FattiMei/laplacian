#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "norm.h"
#include "matrix.h"


void residual(const float b[], const float x[], float r[], int n) {
	action(x, r, n);

	for (int i = 0; i < n; ++i) {
		r[i] = b[i] - r[i];
	}
}


void error(const float xe[], const float x[], float e[], int n) {
	for (int i = 0; i < n; ++i) {
		e[i] = xe[i] - x[i];
	}
}


void setup(float xe[], float b[], int n) {
	for (int i = 0; i < n; ++i) {
		xe[i] = 1.0;
	}

	action(xe, b, n);
}


float xe[NMAX];
float x[NMAX];
float b[NMAX];
float r[NMAX];
float e[NMAX];
float d[NMAX];


int main(int argc, char *argv[]) {
	FILE *out = NULL;
	bool out_needs_fclose = false;


	if (argc == 2) {
		const char *pathname = argv[1];

		out = fopen(argv[1], "w");

		if (out == NULL) {
			fprintf(stderr, "ERROR: can't open file `%s`, quitting\n", pathname);
			exit(EXIT_FAILURE);
		}

		out_needs_fclose = true;
	}
	else {
		out = stdout;
	}


	fprintf(out, "n,residual,error\n");


	for (int n = 10; n <= NMAX; ++n) {
		setup(xe, b, n);
		solve(b, x, n);
		residual(b, x, r, n);
		error(xe, x, e, n);

		fprintf(out, "%d,%e,%e\n", n, norm(r,n), norm(e,n));
	}


	if (out_needs_fclose) {
		fclose(out);
	}


	return 0;
}
