#include <set>
#include <vector>
#include "benchmark/benchmark.h"

static void BM_VectorInsert(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int64_t> insertion_test;
    for (int64_t i = 0, i_end = state.range(0); i < i_end; i++) {
      insertion_test.push_back(i);
    }
  }
}

// Register the function as a benchmark
BENCHMARK(BM_VectorInsert)->Range(8, 8 << 10);

// Define another benchmark
static void BM_SetInsert(benchmark::State &state) {
  for (auto _ : state) {
    std::set<int64_t> insertion_test;
    for (int64_t i = 0, i_end = state.range(0); i < i_end; i++) {
      insertion_test.insert(i);
    }
  }
}
BENCHMARK(BM_SetInsert)->Range(8, 8 << 10);

static void BM_StringCreation(benchmark::State &state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State &state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
