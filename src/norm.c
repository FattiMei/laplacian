#include "config.h"
#include <math.h>
#include <stdlib.h>


float normf(const float x[], int n) {
	float sum = 0.0f;

	for (int i = 0; i < n; ++i) {
		sum += x[i] * x[i];
	}

	return sqrtf(sum);
}


float normd(const float x[], int n) {
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		const double term = x[i];

		sum += term * term;
	}

	return (float) sqrt(sum);
}
