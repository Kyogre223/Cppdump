#include <iostream>
#include <benchmark/benchmark.h>
#include <algorithm>
#include <vector>
#include <thread>


std::atomic<int>shared_counter(0);

std::vector<int>shared_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

static void BM_search(benchmark::State& state) {
	for (auto _ : state) {
        size_t res = 0;
		for (size_t i = 0; i < shared_vector.size(); ++i) {
			if (shared_vector[i] == 1) {
				++res;
			}
		}

        shared_counter.fetch_add(res, std::memory_order_relaxed);
	}
}


BENCHMARK(BM_search)->ThreadRange(1, 120) ->UseRealTime();
BENCHMARK_MAIN();