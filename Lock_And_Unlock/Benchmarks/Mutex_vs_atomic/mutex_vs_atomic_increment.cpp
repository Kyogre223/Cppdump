#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>
#include <iostream>
#include <thread>

// Benchmark for atomic increment
static void BM_AtomicIncrement(benchmark::State& state) {
    static std::atomic<int> atomic_counter(0);
    static std::once_flag flag;
    std::call_once(flag, []() {
        std::cout << "Cores available: " << std::thread::hardware_concurrency() << '\n';
    });
    int const num = 1e5;
    for (auto _ : state) {
        for (int i = 0; i < num; ++i) {
            ++atomic_counter;
            benchmark::DoNotOptimize(atomic_counter);
        }
    }
}
BENCHMARK(BM_AtomicIncrement)->ThreadRange(1, 120)->UseRealTime();

// Benchmark for mutex-protected increment
static void BM_MutexIncrement(benchmark::State& state) {
    static int counter = 0;
    static std::mutex mtx;
    int const num = 1e5;
    for (auto _ : state) {
        for (int i = 0; i < num; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            ++counter;
            benchmark::DoNotOptimize(counter);
        }
    }
}
BENCHMARK(BM_MutexIncrement)->ThreadRange(1, 120)->UseRealTime();

BENCHMARK_MAIN();
