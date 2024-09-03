//
// Created by Lin Kai on 2/9/24.
//

#ifndef CPPDUMP_STD_FUNCTION_H
#define CPPDUMP_STD_FUNCTION_H


#include <iostream>
#include <cstring>
#include <string>
#include <functional>
#include <memory>

// std::function

int add(int a, int b) {
    return a + b;
}

template <typename T>
struct myF;

template <typename Ret, typename... Args>
struct myF<Ret(Args...)> {
    myF(Ret(*f)(Args...)) : ptr_(std::make_unique<child<decltype(f)>>(f)) {
    }

    myF& operator= (Ret(*f)(Args...)) {
        ptr_ = std::make_unique<child<decltype(f)>>(f);
        return *this;
    }

    Ret operator () (Args... args) {
        return ptr_->call(args...);
    }


    struct base {
        base() = default;
        ~base() = default;
        virtual Ret call(Args... args) = 0;
    };

    template <typename T>
    struct child : base {
        child(T data):data_(data) {

        };
        Ret call(Args... args) override {
            return data_(args...);
        }
        T data_;
    };


    std::unique_ptr<base>ptr_;
};



#endif //CPPDUMP_STD_FUNCTION_H
