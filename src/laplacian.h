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
void bad_action(const SINGLE x[], SINGLE y[], int n) {
	for (int i = 0; i < n; ++i) {
		DOUBLE acc = 2.0 * x[i];

		if (i == 0) {
			acc -= x[i+1];
		}
		else if (i == (n-1)) {
			acc -= x[i-1];
		}
		else {
			acc -= static_cast<DOUBLE>(x[i-1]) + static_cast<DOUBLE>(x[i+1]);
		}

		y[i] = static_cast<SINGLE>(acc);
	}
}


template <typename DOUBLE>
inline DOUBLE map(DOUBLE x) {
	return (static_cast<DOUBLE>(2.0) * x - static_cast<DOUBLE>(1.0)) / x;
}


template <typename DOUBLE>
inline DOUBLE inverse_map(DOUBLE x) {
	return static_cast<DOUBLE> (1.0) / (static_cast<DOUBLE>(2.0) - x);
}


template <typename DOUBLE, typename SINGLE>
void thomas(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	DOUBLE d = static_cast<DOUBLE>(2.0);

	diag[0] = static_cast<SINGLE>(d);
	x[0] = b[0];

	for (int i = 1; i < n; ++i) {
		// d = (2 * d - 1) / d with the constants in the same precision as d
		d = map(d);

		diag[i] = static_cast<DOUBLE>(d);
		x[i]   = b[i] + x[i-1] / diag[i-1];
	}

	// backward substitution
	x[n-1] = x[n-1] / diag[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / diag[i];
	}
}


template <typename DOUBLE, typename SINGLE>
void storeless(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	DOUBLE d = static_cast<DOUBLE>(2.0);

	x[0] = b[0];

	for (int i = 1; i < n; ++i) {
		x[i] = b[i] + x[i-1] / d;

		d = map(d);
	}

	// backward substitution
	x[n-1] = x[n-1] / d;

	for (int i = n-2; i >= 0; --i) {
		d = inverse_map(d);
		x[i] = (x[i] + x[i+1]) / d;
	}
}


template <typename DOUBLE, typename SINGLE>
void multifrontal(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	if (n < 3) {
		thomas<DOUBLE>(b, diag, x, n);
		return;
	}

	const int middle = n / 2;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			DOUBLE down = static_cast<DOUBLE>(2.0);
			diag[0]     = static_cast<SINGLE>(down);
			x[0]        = b[0];

			// eliminate downwards
			for (int i = 1; i <= middle; ++i) {
				down = map(down);

				diag[i] = static_cast<SINGLE>(down);
				x[i] = b[i] + x[i-1] / diag[i-1];
			}
		}

		#pragma omp section
		{
			DOUBLE up   = static_cast<DOUBLE>(2.0);
			diag[n-1]   = static_cast<SINGLE>(up);
			x[n-1]      = b[n-1];

			// eliminate upwards
			for (int i = n-2; i > middle; --i) {
				up = map(up);

				diag[i] = static_cast<SINGLE>(up);
				x[i] = b[i] + x[i+1] / diag[i+1];
			}
		}
	}

	// eliminate the first from the second
	diag[middle+1] = diag[middle+1] * diag[middle] - 1.0;
	x[middle+1] = diag[middle] * x[middle+1] + x[middle];

	// the only independent equation
	x[middle+1] = x[middle+1] / diag[middle+1];

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			// backward substitution
			for (int i = middle; i >= 0; --i) {
				x[i] = (x[i] + x[i+1]) / diag[i];
			}
		}

		#pragma omp section
		{
			// forward substitution
			for (int i = middle+2; i < n; ++i) {
				x[i] = (x[i] + x[i-1]) / diag[i];
			}
		}
	}
}


template <typename DOUBLE, typename SINGLE>
void simultaneous(const SINGLE b[], SINGLE diag[], SINGLE x[], int n) {
	if (n < 3) {
		thomas<DOUBLE>(b, diag, x, n);
		return;
	}

	const int middle = n / 2;
	DOUBLE down, up;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			down        = static_cast<DOUBLE>(2.0);
			diag[0]     = static_cast<SINGLE>(down);
			x[0]        = b[0];

			for (int i = 1; i <= middle; ++i) {
				down = map(down);

				diag[i] = static_cast<SINGLE>(down);
				x[i] = b[i] + x[i-1] / diag[i-1];
			}
		}

		#pragma omp section
		{
			up          = static_cast<DOUBLE>(2.0);
			diag[n-1]   = static_cast<SINGLE>(up);
			x[n-1]      = b[n-1];

			for (int i = n-2; i > middle; --i) {
				up = map(up);

				diag[i] = static_cast<SINGLE>(up);
				x[i] = b[i] + x[i+1] / diag[i+1];
			}
		}
	}


	// simultaneous elimination
	SINGLE tmp = x[middle+1];

	diag[middle+1] = static_cast<SINGLE>(up - static_cast<DOUBLE>(1.0) / down);
	x[middle+1] = x[middle+1] + x[middle] / static_cast<SINGLE>(down);

	diag[middle] = static_cast<SINGLE>(down - static_cast<DOUBLE>(1.0) / up);
	x[middle] = x[middle] + tmp / static_cast<SINGLE>(up);


	#pragma omp parallel sections
	{
		#pragma omp section
		{
			x[middle] = x[middle] / diag[middle];

			for (int i = middle-1; i >= 0; --i) {
				x[i] = (x[i] + x[i+1]) / diag[i];
			}
		}

		#pragma omp section
		{
			x[middle+1] = x[middle+1] / diag[middle+1];

			for (int i = middle+2; i < n; ++i) {
				x[i] = (x[i] + x[i-1]) / diag[i];
			}
		}
	}
}


#endif
