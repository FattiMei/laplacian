#include "matrix.h"


void action(const float x[], float y[], int n) {
	for (int i = 0; i < n; ++i) {
		y[i] = x[i];
	}
}


void solve(const float b[], float x[], int n) {
	action(b, x, n);
}
