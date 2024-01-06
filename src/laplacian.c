#include "config.h"
#include "laplacian.h"


float tmp[NMAX];
float upper[NMAX-1];


void laplacian_setup(int n) {
	for (int i = 0; i < n-1; ++i) {
		upper[i] = -1.0f;
	}
}


void actionf(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		y[i] = 2.0f * x[i];

		if (i < (n-1)) {
			y[i] -= x[i+1];
		}

		if (i > 0) {
			y[i] -= x[i-1];
		}
	}
}


void actionf_reordered(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			y[i] = 2.0f * x[i] - x[i+1];
		}
		else if (i == n-1) {
			y[i] = 2.0f * x[i] - x[i-1];
		}
		else {
			y[i] = 2.0f * x[i] - (x[i-1] + x[i+1]);
		}
	}
}


void actiond(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		double acc = 2.0f * x[i];

		if (i < (n-1)) {
			acc -= x[i+1];
		}

		if (i > 0) {
			acc -= x[i-1];
		}

		y[i] = (float) acc;
	}
}


void actiond_reordered(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		double acc = 2.0f * x[i];

		if (i == 0) {
			acc -= x[i+1];
		}
		else if (i == n-1) {
			acc -= x[i-1];
		}
		else {
			const double pred = x[i-1];
			const double succ = x[i+1];

			acc -= (pred + succ);
		}

		y[i] = (float) acc;
	}
}


void solve_naive(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		tmp[i] = 2.0f - 1.0f / tmp[i-1];
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}


void solvef(const float b[], float x[], int n) {
	float d = 2.0f;

	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		d = (2.0f * d - 1.0f) / d;

		tmp[i] = (float) d;
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}


void solved(const float b[], float x[], int n) {
	double d = 2.0;

	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		d = (2.0 * d - 1.0) / d;

		tmp[i] = (float) d;
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}


void solve_better(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];

	for (int i = 1; i < n; ++i) {
		tmp[i] = (2.0f * tmp[i-1] - 1.0f) / tmp[i-1];
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}
}


void solve_upper(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];


	laplacian_setup(n);


	for (int i = 1; i < n; ++i) {
		tmp[i] = 2.0f + upper[i-1] / tmp[i-1];

		if (tmp[i] == tmp[i-1]) {
			// riscalamento riga
			tmp[i] = 2.0f * tmp[i-1];
			upper[i] *= tmp[i-1];

			// eliminazione
			tmp[i] += upper[i-1];
			x[i] = tmp[i-1] * b[i] + x[i-1];
		}
		else {
			x[i] = b[i] + x[i-1] / tmp[i-1];
		}
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] - upper[i] * x[i+1]) / tmp[i];
	}
}


void solve_upper_better(const float b[], float x[], int n) {
	// eliminazione
	tmp[0] = 2.0f;
	x[0]   = b[0];


	laplacian_setup(n);


	for (int i = 1; i < n; ++i) {
		tmp[i] = (2.0f * tmp[i-1] + upper[i-1]) / tmp[i-1];

		if (tmp[i] == tmp[i-1]) {
			// riscalamento riga
			tmp[i] = 2.0f * tmp[i-1];
			upper[i] *= tmp[i-1];

			// eliminazione
			tmp[i] += upper[i-1];
			x[i] = tmp[i-1] * b[i] + x[i-1];
		}
		else {
			x[i] = b[i] + x[i-1] / tmp[i-1];
		}
	}

	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] - upper[i] * x[i+1]) / tmp[i];
	}
}


// default implementation
void solve(const float b[], float x[], int n) {
	solve_better(b, x, n);
}
