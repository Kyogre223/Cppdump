//
// Created by Lin Kai on 14/11/24.
//

#include <iostream>
#include <benchmark/benchmark.h>
#include <atomic>
#include <memory>
#include <optional>
#include <cstdlib>
#include <new>
#include <cassert>

// template <typename T, typename Alloc = std::allocator<T>>
// class Fifo1 : private Alloc {
//     std::size_t capacity_;
//     T* ring_;
//     std::size_t pushCursor{};
//     std::size_t popCursor{};

// public:
//     explicit Fifo1(std::size_t capacity, Alloc const& alloc = Alloc{})
//         : Alloc{alloc}, capacity_{capacity}, ring_{std::allocator_traits<Alloc>::allocate(*this, capacity)} {}

//     ~Fifo1() {
//         while (!empty()) {
//             ring_[popCursor % capacity_].~T();
//             ++popCursor;
//         }
//         std::allocator_traits<Alloc>::deallocate(*this, ring_, capacity_);
//     }

//     auto capacity() const { return capacity_; }
//     auto size() const { return pushCursor - popCursor; }
//     auto empty() const { return size() == 0; }
//     auto full() const { return size() == capacity(); }

//     bool push(T const& value);
//     bool pop(T& value);
// };

// template <typename T, typename Alloc>
// bool Fifo1<T, Alloc>::push(T const& value) {
//     if (full()) return false;
//     new (&ring_[pushCursor % capacity_]) T(value);
//     ++pushCursor;
//     return true;
// }

// template <typename T, typename Alloc>
// bool Fifo1<T, Alloc>::pop(T& value) {
//     if (empty()) return false;
//     value = ring_[popCursor % capacity_];
//     ring_[popCursor % capacity_].~T();
//     ++popCursor;
//     return true;
// }

template <typename T, typename Alloc = std::allocator<T>>
class Fifo2 : private Alloc {
    std::size_t capacity_;
    T* ring_;

    static_assert(std::atomic<std::size_t>::is_always_lock_free, "Atomic size_t must be lock-free");

    alignas(64) std::atomic<std::size_t> pushCursor_{0};
    alignas(64) std::atomic<std::size_t> popCursor_{0};

public:
    explicit Fifo2(std::size_t capacity, Alloc const& alloc = Alloc{})
            : Alloc{alloc}, capacity_{capacity}, ring_{std::allocator_traits<Alloc>::allocate(*this, capacity)} {}

    ~Fifo2() {
        size_t currentPop = popCursor_.load(std::memory_order_relaxed);
        size_t currentPush = pushCursor_.load(std::memory_order_relaxed);
        while (currentPop < currentPush) {
            ring_[currentPop % capacity_].~T();
            ++currentPop;
        }
        std::allocator_traits<Alloc>::deallocate(*this, ring_, capacity_);
    }

    auto capacity() const { return capacity_; }
    auto size() const { return pushCursor_.load(std::memory_order_relaxed) - popCursor_.load(std::memory_order_relaxed); }
    auto empty() const { return size() == 0; }
    auto full() const { return size() == capacity(); }

    bool push(T const& value);
    bool pop(T& value);
};

template <typename T, typename Alloc>
bool Fifo2<T, Alloc>::push(T const& value) {
    size_t currentPush = pushCursor_.load(std::memory_order_relaxed);
    size_t currentPop = popCursor_.load(std::memory_order_acquire);
    if (currentPush - currentPop >= capacity_) {
        return false; // Queue is full
    }
    new (&ring_[currentPush % capacity_]) T(value);
    pushCursor_.store(currentPush + 1, std::memory_order_release);
    return true;
}

template <typename T, typename Alloc>
bool Fifo2<T, Alloc>::pop(T& value) {
    size_t currentPop = popCursor_.load(std::memory_order_relaxed);
    size_t currentPush = pushCursor_.load(std::memory_order_acquire);
    if (currentPop == currentPush) {
        return false; // Queue is empty
    }
    value = ring_[currentPop % capacity_];
    ring_[currentPop % capacity_].~T();
    popCursor_.store(currentPop + 1, std::memory_order_release);
    return true;
}



Fifo2<size_t> queue_2(1UL << 15);

template <typename T, typename Alloc = std::allocator<T>>
class Fifo3 : private Alloc {
    std::size_t capacity_;
    T* ring_;

    static_assert(std::atomic<std::size_t>::is_always_lock_free, "Atomic size_t must be lock-free");

    alignas(64) std::atomic<std::size_t> pushCursor_{0};
    alignas(64) std::atomic<std::size_t> popCursor_{0};

public:
    explicit Fifo3(std::size_t capacity, Alloc const& alloc = Alloc{})
            : Alloc{alloc}, capacity_{capacity}, ring_{std::allocator_traits<Alloc>::allocate(*this, capacity)} {}

    ~Fifo3() {
        size_t currentPop = popCursor_.load(std::memory_order_relaxed);
        size_t currentPush = pushCursor_.load(std::memory_order_relaxed);
        while (currentPop < currentPush) {
            ring_[currentPop % capacity_].~T();
            ++currentPop;
        }
        std::allocator_traits<Alloc>::deallocate(*this, ring_, capacity_);
    }

    auto capacity() const { return capacity_; }
    auto size() const { return pushCursor_.load(std::memory_order_relaxed) - popCursor_.load(std::memory_order_relaxed); }
    auto empty() const { return size() == 0; }
    auto full() const { return size() == capacity(); }
    auto full(std::size_t pushCursor, std::size_t popCursor) const {
        return (pushCursor - popCursor) == capacity_;
    }
    static auto empty(std::size_t pushCursor, std::size_t popCursor) {
        return pushCursor == popCursor;
    }
    auto element(std::size_t cursor) {
        return &ring_[cursor%capacity_];
    }
    bool push(T const& value);
    bool pop(T& value);
};

template <typename T, typename Alloc>
bool Fifo3<T, Alloc>::push(T const& value) {
    size_t currentPush = pushCursor_.load(std::memory_order_relaxed);
    size_t currentPop = popCursor_.load(std::memory_order_acquire);
    if (full(currentPush, currentPop)) {
        return false; // Queue is full
    }
    new (element(currentPush)) T(value);
    pushCursor_.store(currentPush + 1, std::memory_order_release);
    return true;
}

template <typename T, typename Alloc>
bool Fifo3<T, Alloc>::pop(T& value) {
    size_t currentPop = popCursor_.load(std::memory_order_relaxed);
    size_t currentPush = pushCursor_.load(std::memory_order_acquire);
    if (currentPop == currentPush) {
        return false; // Queue is empty
    }
    value = *element(currentPop);
    element(currentPop)->~T();
    popCursor_.store(currentPop + 1, std::memory_order_release);
    return true;
}

// static void BM_FIFO1(benchmark::State& state) {
//     int N = 1e5;
//     for (auto _ : state) {
//         for (int i = 0; i < N; ++i) { // Changed to i < N to push N elements
//             queue_.push(i);
//         }
//         std::size_t x;
//         for (int i = 0; i < N; ++i) { // Changed to i < N to pop N elements
//             benchmark::DoNotOptimize(queue_.pop(x));
//         }
//     }

//     state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
// }

#include <atomic>
#include <cstddef>
#include <memory>

template <typename T>
class Fifo4 {
private:
    std::atomic<std::size_t> pushCursor_{0};
    std::size_t localPush_{0};
    std::atomic<std::size_t> popCursor_{0};
    std::size_t localPop_{0};
    std::size_t cap_ = 0;
    T* ring_;
    std::allocator<T> allocator_;

public:
    explicit Fifo4(std::size_t capacity = 1000000) : cap_{capacity} {
        static_assert(std::atomic<std::size_t>::is_always_lock_free,
                      "std::atomic<std::size_t> must be lock-free.");
        ring_ = allocator_.allocate(cap_);
    }

    ~Fifo4() {
        std::size_t currentPop = popCursor_.load(std::memory_order_relaxed);
        std::size_t currentPush = pushCursor_.load(std::memory_order_relaxed);
        while (currentPop < currentPush) {
            ring_[currentPop % cap_].~T();
            ++currentPop;
        }
        allocator_.deallocate(ring_, cap_);
    }

    bool full(std::size_t left, std::size_t right) const {
        return (left - right) >= cap_;
    }

    bool empty(std::size_t left, std::size_t right) const {
        return left == right;
    }

    bool push(T const& v) {
        std::size_t old_push = pushCursor_.load(std::memory_order_relaxed);
        if (full(old_push, localPop_)) {
            localPop_ = popCursor_.load(std::memory_order_acquire);
            if (full(old_push, localPop_))
                return false;
        }
        new (&ring_[old_push % cap_]) T(v);
        pushCursor_.store(old_push + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& v) {
        std::size_t old_pop = popCursor_.load(std::memory_order_relaxed);
        if (empty(localPush_, old_pop)) {
            localPush_ = pushCursor_.load(std::memory_order_acquire);
            if (empty(localPush_, old_pop))
                return false;
        }
        v = ring_[old_pop % cap_];
        ring_[old_pop % cap_].~T();
        popCursor_.store(old_pop + 1, std::memory_order_release);
        return true;
    }
};

static void BM_FIFO3(benchmark::State& state) {
    long long N = 1e7;
    Fifo3<std::size_t>q3(1UL << 15);
    for (auto _ : state) {

        for (int i = 0; i < N; ++i) { // Changed to i < N to push N elements
            q3.push(i);
        }
        std::size_t x;
        for (int i = 0; i < N; ++i) { // Changed to i < N to pop N elements
            benchmark::DoNotOptimize(q3.pop(x));
        }
    }

    state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

static void BM_FIFO4(benchmark::State& state) {
    long long N = 1e7;
    Fifo4<std::size_t>q3(1UL << 15);
    for (auto _ : state) {

        for (int i = 0; i < N; ++i) { // Changed to i < N to push N elements
            q3.push(i);
        }
        std::size_t x;
        for (int i = 0; i < N; ++i) { // Changed to i < N to pop N elements
            benchmark::DoNotOptimize(q3.pop(x));
        }
    }

    state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

BENCHMARK(BM_FIFO3)->Threads(2)->UseRealTime();
BENCHMARK(BM_FIFO4)->Threads(2)->UseRealTime();

BENCHMARK_MAIN();
