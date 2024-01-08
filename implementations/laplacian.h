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


template <typename DOUBLE>
inline DOUBLE map(DOUBLE x) {
	return (static_cast<DOUBLE>(2.0) * x - static_cast<DOUBLE>(1.0)) / x;
}


template <typename DOUBLE, typename SINGLE>
void thomas(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	DOUBLE d = static_cast<DOUBLE>(2.0);


	diag[0] = static_cast<SINGLE>(d);
	x[0] = b[0];


	for (int i = 1; i < n; ++i) {
		// d = (2 * d - 1) / d con le costanti nella precisione di d;
		d = map(d);

		diag[i] = static_cast<DOUBLE>(d);
		x[i]   = b[i] + x[i-1] / diag[i-1];
	}


	// sostituzione all'indietro
	x[n-1] = x[n-1] / diag[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / diag[i];
	}
}


template <typename DOUBLE, typename SINGLE>
void multifrontal(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	if (n < 3) {
		thomas<DOUBLE>(b, diag, x, n);
	}
	else {
		DOUBLE down = static_cast<DOUBLE>(2.0);
		DOUBLE up   = static_cast<DOUBLE>(2.0);

		diag[0]     = static_cast<SINGLE>(down);
		diag[n-1]   = static_cast<SINGLE>(up);

		x[0]        = b[0];
		x[n-1]      = b[n-1];


		const int endstop = n / 2;


		// elimino verso il basso
		for (int i = 1; i <= endstop; ++i) {
			down = map(down);

			diag[i] = static_cast<SINGLE>(down);
			x[i] = b[i] + x[i-1] / diag[i-1];
		}

		// elimino verso l'alto
		for (int i = n-2; i > endstop; --i) {
			up = map(up);

			diag[i] = static_cast<SINGLE>(up);
			x[i] = b[i] + x[i+1] / diag[i+1];
		}

		// elimino la prima dalla seconda
		diag[endstop+1] = diag[endstop+1] * diag[endstop] - 1.0f;
		x[endstop+1] = diag[endstop] * x[endstop+1] + x[endstop];

		// l'unica equazione indipendente
		x[endstop+1] = x[endstop+1] / diag[endstop+1];

		// sostituisco all'indietro
		for (int i = endstop; i >= 0; --i) {
			x[i] = (x[i] + x[i+1]) / diag[i];
		}

		// sostituisco in avanti
		for (int i = endstop+2; i < n; ++i) {
			x[i] = (x[i] + x[i-1]) / diag[i];
		}
	}
}


#endif
