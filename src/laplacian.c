#include "config.h"
#include "matrix.h"
#include "laplacian.h"


float tmp[NMAX];


void actionf(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		y[i] = 2.0 * x[i];

		if (i < (n-1)) {
			y[i] -= x[i+1];
		}

		if (i > 0) {
			y[i] -= x[i-1];
		}
	}
}


void actiond(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		double acc = 2.0 * x[i];

		if (i < (n-1)) {
			acc -= x[i+1];
		}

		if (i > 0) {
			acc -= x[i-1];
		}

		y[i] = (float) acc;
	}
}


void action_naive(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		y[i] = 2.0 * x[i];

		if (i < (n-1)) {
			y[i] -= x[i+1];
		}

		if (i > 0) {
			y[i] -= x[i-1];
		}
	}
}


void action(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			y[i] = 2.0 * x[i] - x[i+1];
		}
		else if (i == (n-1)) {
			y[i] = 2.0 * x[i] - x[i-1];
		}
		else {
			y[i] = 2.0 * x[i] - (x[i-1] + x[i+1]);
		}
	}
}


void solve_naive(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		tmp[i] = 2.0 - 1.0 / tmp[i-1];
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}


void solve(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		tmp[i] = (2.0 * tmp[i-1] - 1.0) / tmp[i-1];
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}
