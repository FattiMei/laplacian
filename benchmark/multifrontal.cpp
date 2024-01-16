#include <benchmark/benchmark.h>
#include "norm.h"
#include "laplacian.h"


#define NMAX 10000


float x[NMAX];
float b[NMAX];
float diag[NMAX];


void init(float b[], int n) {
	for (int i = 0; i < n; ++i) {
		b[i] = 1;
	}
}


static void thomas_fp32(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		thomas<float>(b, diag, x, n);
	}
}


static void multifrontal_fp32(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		multifrontal<float>(b, diag, x, n);
	}
}


// Benefits of parallelism in elimination procedure
// @TODO: test on different system dimension
BENCHMARK(thomas_fp32)->Arg(NMAX);
BENCHMARK(multifrontal_fp32)->Arg(NMAX);

BENCHMARK_MAIN();
