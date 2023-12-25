#include "config.h"
#include <math.h>
#include <stdlib.h>


int real_comparison(const void *x, const void *y) {
	return *((float *) x) < *((float *) y);
}


double norm(const float x[], int n) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrt(sum);
}


// this function invalidates the contents of x
double norm_ordered(float x[], int n) {
	double sum = 0.0;


	for (int i = 0; i < n; ++i) {
		x[i] *= x[i];
	}

	qsort(x, n, sizeof(float), &real_comparison);

	for (int i = 0; i < n; ++i) {
		sum += (double) x[i];
	}

	return sqrt(sum);
}


double norm_kahan(const float x[], int n) {
	// https://en.wikipedia.org/wiki/Kahan_summation_algorithm
	double sum = 0.0;
	double c = 0.0;


	for (int i = 0; i < n; ++i) {
		const double y = x[i] * x[i] - c;
		const double t = sum + y;

		c = (t - sum) - y;
		sum = t;
	}

	return sqrt(sum);
}


// this function invalidates the contents of x
double norm_kahan_ordered(float x[], int n) {
	for (int i = 0; i < n; ++i) {
		x[i] *= x[i];
	}

	qsort(x, n, sizeof(float), &real_comparison);


	// https://en.wikipedia.org/wiki/Kahan_summation_algorithm
	double sum = 0.0;
	double c = 0.0;


	for (int i = 0; i < n; ++i) {
		const double y = x[i] - c;
		const double t = sum + y;

		c = (t - sum) - y;
		sum = t;
	}

	return sqrt(sum);
}
