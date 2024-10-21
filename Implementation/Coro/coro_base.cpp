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
