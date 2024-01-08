#ifndef __LAPLACIAN_H__
#define __LAPLACIAN_H__


template <typename DOUBLE, typename SINGLE>
void thomas(const SINGLE b[], SINGLE x[], int n) {
	// è un peccato dover fare questa allocazione, ma è il prezzo da pagare per i template
	SINGLE tmp[] = new SINGLE[n];
	DOUBLE d = static_cast<DOUBLE>(2.0);


	tmp[0] = static_cast<SINGLE>(d);
	x[0] = b[0];


	for (int i = 1; i < n; ++i) {
		// d = (2 * d - 1) / d con le costanti nella precisione di d;
		d = (static_cast<DOUBLE>(2.0) * d - static_cast<DOUBLE>(1.0)) / d;

		tmp[i] = static_cast<DOUBLE> d;
		x[i]   = b[i] + x[i-1] / tmp[i-1];
	}


	// sostituzione all'indietro
	x[n-1] = x[n-1] / tmp[n-1];

	for (int i = n-2; i >= 0; --i) {
		x[i] = (x[i] + x[i+1]) / tmp[i];
	}


	delete[] tmp;
}


#endif
