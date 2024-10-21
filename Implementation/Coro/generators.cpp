//
// Created by Lin Kai on 14/10/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <coroutine>
#include <bits/stdc++.h>

// basic coro
class Coro {
public:
    struct promise_type {
        auto get_return_object() {
            return Coro{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        auto initial_suspend() {return std::suspend_always{};}

        auto final_suspend() noexcept {return std::suspend_always{};}

        void return_void() const {

        }

        void unhandled_exception() { std::terminate();}
    };
    std::coroutine_handle<promise_type>h_;
    explicit Coro(std::coroutine_handle<promise_type> h):h_{h}{}
    Coro(Coro&& r):h_{std::exchange(r.h_, {})}{}
    ~Coro(){
        if (h_){
            h_.destroy();
        }
    }

    bool resume() {
        if (!h_.done()) {h_.resume();}
        return !h_.done();
    }
};


template <typename T>
class Generator {
    struct Promise {
        T value_;
        auto get_return_object() {
            return Generator(std::coroutine_handle<Promise>::from_promise(*this));
        }
        void return_void() {
            return;
        }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto yield_value(T&& value) {
            value_ = value;
            return std::suspend_always{};
        }
        auto yield_value(T const& value) {
            value_ = value;
            return std::suspend_always{};
        }

    };
    struct Sentinel {};
    struct Iterator {};
    std::coroutine_handle<Promise>h_;
public:
    using promise_type = Promise;
    Generator(std::coroutine_handle<promise_type> h):h_{h}{}
    Generator(Generator&& g): h_{std::exchange(g.h_, {})} {}
    ~Generator() {if (h_) {h_.destroy();}}

    auto begin() {
        h_.resume();
        return Iterator{h_};
    }
    auto end() {
        return Sentinel{};
    }


};


struct Widget {
    auto coroutine() -> Coro {
        std::cout << ++i_ << " ";
        co_await std::suspend_always{};
        std::cout << ++i_ << " ";
        std::cout << '\n';
    }

private:
    int i_{};
};


int main() {
    Widget w;
    auto coro = w.coroutine();
    while (coro.resume()) {
        std::cout << "While looped\n";
    }




    return 0;
}
