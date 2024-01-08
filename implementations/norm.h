#ifndef __NORM_H__
#define __NORM_H__


#include <cmath>


template <typename DOUBLE, typename SINGLE>
DOUBLE norm(const SINGLE x[], int n) {
	DOUBLE sum = 0.0;

	for (int i = 0; i < n; ++i) {
		const DOUBLE term = static_cast<DOUBLE>(x[i]);

		sum += term * term;
	}

	return std::sqrt(sum);
}


#endif
