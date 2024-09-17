//
// Created by Lin Kai on 17/9/24.
//

#ifndef CPPDUMP_FUNCTION_H
#define CPPDUMP_FUNCTION_H


#include <iostream>
#include <memory>

// threadpool
// variant
// function ( try this)
// any

// unique ptr
// shared_ptr
// string ?
// malloc


template <typename T>
struct Function;



template <typename Ret, typename... Args>
struct Function<Ret(Args...)> {
    Function(Ret(*f)(Args...)):ptr_(std::make_unique<Child<decltype(f)>>(f)) {

    }

    Ret operator()(Args... args) {
        return ptr_->call(args...);
    }
    struct Base {
        Base() = default;
        virtual ~Base() = default;
        virtual Ret call(Args...) = 0;
    };
    template <typename T>
    struct Child: Base {
        Child(T data):data_(data){

        }
        Ret call(Args... args) override {
            return data_(args...);
        }
        ~Child() {

        }

        T data_;

    };


    std::unique_ptr<Base>ptr_;
};
void foo(int a, int b) {
    std::cout << a + b << '\n';
    return;
}



#endif //CPPDUMP_FUNCTION_H
