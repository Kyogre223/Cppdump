//
// Created by Lin Kai on 9/11/24.
//


#include <optional>
#include <deque>
#include <mutex>
#include <unistd.h>


template <typename T>
class mt_stack {
    std::deque<T>s_;
    int cap_ = 0;
    struct counts_t {
        int pc_;
        int cc_;
        bool equal(std::atomic<counts_t>& n) {
            if (pc_ == cc_) return true;
            *this = n.load(std::memory_order_relaxed);
            return false;
        }
    };
    mutable std::atomic<counts_t>n_;

    void push(T const& v) {
        counts_t n = n_.load(std::memory_order_relaxed);
        while (!n.equal(n_) || !n_.compare_exchange_weak(n, {n.pc_ + 1, n.cc_}, std::memory_order_acquire, std::memory_order_relaxed)) {
            if (n.pc_ == cap_) abort();
        }
        n.pc_++;
        new (&s_[n.pc_]) T(v);

        if (!n_.compare_exchange_strong(n, {n.pc_, n.cc_+1}, std::memory_order_release, std::memory_order_relaxed)) abort();
    }

    std::optional<T> pop() const {
        counts_t n = n_.load(std::memory_order_relaxed);
        if (n.cc_ == 0) return std::optional<T>(std::nullopt);

        while (!n.equal(n_) || !n_.compare_exchange_weak(n, {n.pc_, n.cc_- 1}, std::memory_order_acquire, std::memory_order_relaxed)) {
            if (n.cc_ == 0) return std::optional<T>(std::nullopt);
        }
        n.cc_--;
        // destructor for the
        std::optional<T> res(std::move(s_[n.cc_]));
        (s_[n.cc_]).~T();
        if (!n_.compare_exchange_strong(n, {n.pc_ - 1, n.cc}, std::memory_order_release, std::memory_order_relaxed)) abort();
        return res;
    }
};