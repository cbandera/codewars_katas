#include "decompose.hpp"
#include <benchmark/benchmark.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <tuple>

static void BM_DecomposeOwn(benchmark::State &state) {
  for (auto _ : state) {
    Decomp::decompose(state.range(0));
  }
  state.SetComplexityN(state.range(0));
}

static void BM_DecomposeOther(benchmark::State &state) {
  for (auto _ : state) {
    Decomp::Decomp::decompose(state.range(0));
  }
  state.SetComplexityN(state.range(0));
}

static const long long maxNumber =
    1234567; //    Decomp::internal::next_best_guess(std::numeric_limits<long
             //    long>::max(),std::numeric_limits<long long>::max());
BENCHMARK(BM_DecomposeOwn)
    ->RangeMultiplier(3)
    ->Range(2, maxNumber)
    ->Complexity();
BENCHMARK(BM_DecomposeOther)
    ->RangeMultiplier(3)
    ->Range(2, maxNumber)
    ->Complexity();

BENCHMARK_MAIN();
