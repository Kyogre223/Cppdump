//
// Created by Lin Kai on 6/9/24.
//

#ifndef CPPDUMP_BASIC_CORO_H
#define CPPDUMP_BASIC_CORO_H


#include <iostream>
#include <coroutine>



struct coro {
    struct promise_type {
        auto final_suspend() noexcept {
            return std::suspend_always{};
        }

        auto initial_suspend() {
            return std::suspend_always{};
        }

        void unhandled_exception () {
            std::terminate();
        }

        void return_void() {
            return;
        }

        auto get_return_object() {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            return coro{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
    };

    std::coroutine_handle<promise_type>hdl_;

    coro(auto T):hdl_(T) {

    }
    ~coro() {
        if (hdl_)hdl_.destroy();
    }

    bool resume() {
        if (!hdl_ || hdl_.done()) return false;
        hdl_.resume();

        return !hdl_.done();
    }
};



#endif //CPPDUMP_BASIC_CORO_H
