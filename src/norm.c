#include "config.h"
#include <math.h>
#include <stdlib.h>


int real_comparison(const void *x, const void *y) {
	return *((float *) x) < *((float *) y);
}


float normf(const float x[], int n) {
	float sum = 0.0f;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrtf(sum);
}


// this function invalidates the contents of x
float normf_ordered(float x[], int n) {
	float sum = 0.0f;

	for (int i = 0; i < n; ++i) {
		x[i] = x[i] * x[i];
	}

	qsort(x, n, sizeof(float), real_comparison);

	for (int i = 0; i < n; ++i) {
		sum += x[i];
	}

	return sqrtf(sum);
}


double normd(const float x[], int n) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		const double term = x[i];

		sum += term * term;
	}

	return sqrt(sum);
}
