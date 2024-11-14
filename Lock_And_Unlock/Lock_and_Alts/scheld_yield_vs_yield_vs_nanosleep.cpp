#include <iostream>
#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
#include <unistd.h>

// First, define the spin lock classes.

class spinlock {
    std::atomic<int> flag = {0};
public:
    void lock() {
        while (flag.load(std::memory_order_relaxed) || flag.exchange(1, std::memory_order_acquire)) {
            // Busy-wait
        }
    }
    void unlock() {
        flag.store(0, std::memory_order_release);
    }
};

static const timespec ns = {0, 1};

class spinlock2 {
    std::atomic<int> flag = {0};
public:
    void lock() {
        int i = 0;
        while (flag.load(std::memory_order_relaxed) || flag.exchange(1, std::memory_order_acquire)) {
            ++i;
            if (i == 8) {
                nanosleep(&ns, NULL);
                i = 0;
            }
        }
    }
    void unlock() {
        flag.store(0, std::memory_order_release);
    }
};

class spinlock_yield {
    std::atomic<int> flag = {0};
public:
    void lock() {
        int i = 0;
        while (flag.load(std::memory_order_relaxed) || flag.exchange(1, std::memory_order_acquire)) {
            ++i;
            if (i == 8) {
                std::this_thread::yield();
                i = 0;
            }
        }
    }
    void unlock() {
        flag.store(0, std::memory_order_release);
    }
};

class spinlock_sched_yield {
    std::atomic<int> flag = {0};
public:
    void lock() {
        int i = 0;
        while (flag.load(std::memory_order_relaxed) || flag.exchange(1, std::memory_order_acquire)) {
            ++i;
            if (i == 8) {
                sched_yield();
                i = 0;
            }
        }
    }
    void unlock() {
        flag.store(0, std::memory_order_release);
    }
};

// Now, set up the benchmarking function.

static const int N = 1e6;  // Number of increments per thread

static void BM_SpinLock2(benchmark::State& state) {
    spinlock2 lock_;

    for (auto _ : state) {
        // Each thread increments the shared counter N times.
        int c = 0;
        for (int i = 0; i < N; ++i) {
            lock_.lock();
            ++c;
            lock_.unlock();
        }
    }
    state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

static void BM_SpinLockYield(benchmark::State& state) {

    spinlock_yield lock_;

    for (auto _ : state) {
        // Each thread increments the shared counter N times.
        int c = 0;
        for (int i = 0; i < N; ++i) {
            lock_.lock();
            ++c;
            lock_.unlock();
        }
    }
    state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

static void BM_SpinLockSchedYield(benchmark::State& state) {

    spinlock_sched_yield lock_;

    for (auto _ : state) {
        // Each thread increments the shared counter N times.
        int c = 0;
        for (int i = 0; i < N; ++i) {
            lock_.lock();
            ++c;
            lock_.unlock();
        }
    }
    state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

BENCHMARK(BM_SpinLock2)->ThreadRange(1, 50)->UseRealTime();
BENCHMARK(BM_SpinLockYield)->ThreadRange(1, 50)->UseRealTime();
BENCHMARK(BM_SpinLockSchedYield)->ThreadRange(1, 50)->UseRealTime();
// Run the benchmarks.
BENCHMARK_MAIN();
