#include "config.h"
#include <math.h>


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


float norminf(const float x[], int n) {
	float min = 0.0;

	for (int i = 0; i < n; ++i) {
		const float y = fabsf(x[i]);

		if (y < min) {
			min = y;
		}
	}

	return min;
}


// default implementation
float norm(const float x[], int n) {
	return normd(x, n);
}
