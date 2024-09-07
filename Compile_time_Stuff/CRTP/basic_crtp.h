//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_BASIC_CRTP_H
#define CPPDUMP_BASIC_CRTP_H


#include <iostream>

// CRTP example

template <typename B>
struct A {
    void call() {
        static_cast<B*>(this)->call();
    }
};


struct B : public A<B> {
    void call() {
        std::cout << "I am B!\n";
    }
};


#endif //CPPDUMP_BASIC_CRTP_H
