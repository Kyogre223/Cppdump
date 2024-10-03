//
// Created by Lin Kai on 2/10/24.
//
#include <atomic>




class SpinLock {
public:
    SpinLock() {
        flag_ = 0;
    }
    // set the flag to 1.
    void lock() {
        while (flag_.load(std::memory_order_relaxed), flag_.exchange(1, std::memory_order_acquire)) {}
    }
    void unlock() {
        flag_.store(0, std::memory_order_release);
    }

private:
    std::atomic<int>flag_;
};
