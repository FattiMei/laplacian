#include <benchmark/benchmark.h>
#include "laplacian.h"


#ifndef NMAX
#define NMAX 10000
#endif


#ifndef REAL
#define REAL float
#endif


REAL x[NMAX];
REAL b[NMAX];
REAL diag[NMAX];


void init(float b[], int n) {
	for (int i = 0; i < n; ++i) {
		b[i] = i;
	}
}


template <typename DOUBLE>
static void thomas(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		thomas<DOUBLE>(b, diag, x, n);
	}
}


BENCHMARK(thomas<float>)->RangeMultiplier(2)->Range(10, NMAX)->Complexity();
BENCHMARK(thomas<double>)->RangeMultiplier(2)->Range(10, NMAX)->Complexity();

BENCHMARK_MAIN();
