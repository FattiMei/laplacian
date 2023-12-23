#include "config.h"
#include "matrix.h"


Real tmp[NMAX];


void action(const Real x[], Real y[], int n) {
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


void solve(const Real b[], Real x[], int n) {
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
