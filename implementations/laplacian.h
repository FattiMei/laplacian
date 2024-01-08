#ifndef __LAPLACIAN_H__
#define __LAPLACIAN_H__


template <typename DOUBLE, typename SINGLE>
void action(const SINGLE x[], SINGLE y[], int n) {
	for (int i = 0; i < n; ++i) {
		DOUBLE acc = 2.0 * x[i];

		if (i < (n-1)) {
			acc -= x[i+1];
		}
		if (i > 0) {
			acc -= x[i-1];
		}

		y[i] = static_cast<SINGLE>(acc);
	}
}


template <typename DOUBLE, typename SINGLE>
void thomas(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	DOUBLE d = static_cast<DOUBLE>(2.0);


	diag[0] = static_cast<SINGLE>(d);
	x[0] = b[0];


	for (int i = 1; i < n; ++i) {
		// d = (2 * d - 1) / d con le costanti nella precisione di d;
		d = (static_cast<DOUBLE>(2.0) * d - static_cast<DOUBLE>(1.0)) / d;

		diag[i] = static_cast<DOUBLE>(d);
		x[i]   = b[i] + x[i-1] / diag[i-1];
	}


	// sostituzione all'indietro
	x[n-1] = x[n-1] / diag[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / diag[i];
	}
}


#endif
