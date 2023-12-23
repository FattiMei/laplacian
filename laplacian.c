#include "matrix.h"


void action(int n, const float x[], float y[]) {
	for (int i = 0; i < n; ++i) {
		y[i] = x[i];
	}
}


void solve(int n, const float b[], float x[], float tmp[]) {
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
