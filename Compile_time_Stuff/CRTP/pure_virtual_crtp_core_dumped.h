//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_PURE_VIRTUAL_CRTP_CORE_DUMPED_H
#define CPPDUMP_PURE_VIRTUAL_CRTP_CORE_DUMPED_H


#include <iostream>

// CRTP example

template <typename B>
struct A {
    void call() {
        static_cast<B*>(this)->call();
    }
};


struct B : public A<B> {
    // no call here ?
};

#endif //CPPDUMP_PURE_VIRTUAL_CRTP_CORE_DUMPED_H
