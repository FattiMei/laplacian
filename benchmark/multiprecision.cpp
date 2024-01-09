#include <benchmark/benchmark.h>
#include "norm.h"


void init(float x[], int n) {
	for (int i = 0; i < n; ++i) {
		x[i] = i;
	}
}


static void norm_fp32(benchmark::State& state) {
	const int n = state.range(0);
	float *x = new float[n];

	init(x, n);

	for (auto _ : state) {
		norm<float>(x,n);
	}
}


static void norm_fp64(benchmark::State& state) {
	const int n = state.range(0);
	float *x = new float[n];

	init(x, n);

	for (auto _ : state) {
		norm<double>(x,n);
	}
}


static void norm_fp80(benchmark::State& state) {
	const int n = state.range(0);
	float *x = new float[n];

	init(x, n);

	for (auto _ : state) {
		norm<long double>(x,n);
	}
}


BENCHMARK(norm_fp32)->Arg(100000);
BENCHMARK(norm_fp64)->Arg(100000);
BENCHMARK(norm_fp80)->Arg(100000);
BENCHMARK_MAIN();
