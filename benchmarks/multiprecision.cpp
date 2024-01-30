#include <benchmark/benchmark.h>
#include "norm.h"


#define NMAX 100000


float x[NMAX];


void init(float x[], int n) {
	for (int i = 0; i < n; ++i) {
		x[i] = i;
	}
}


static void norm_fp32(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		norm<float>(x,n);
	}
}


static void norm_fp64(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		norm<double>(x,n);
	}
}


static void norm_fp80(benchmark::State& state) {
	const int n = state.range(0);

	init(x, n);

	for (auto _ : state) {
		norm<long double>(x,n);
	}
}


// How norm calculation suffers from the precision used
BENCHMARK(norm_fp32)->Arg(NMAX);
BENCHMARK(norm_fp64)->Arg(NMAX);
BENCHMARK(norm_fp80)->Arg(NMAX);

BENCHMARK_MAIN();


