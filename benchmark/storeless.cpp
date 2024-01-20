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


static void thomas_fp64(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		thomas<double>(b, diag, x, n);
	}
}


static void storeless_fp64(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		storeless<double>(b, diag, x, n);
	}
}


// Benefits of non accessing the diagonal array
BENCHMARK(thomas_fp64)->Arg(NMAX);
BENCHMARK(storeless_fp64)->Arg(NMAX);

BENCHMARK_MAIN();
