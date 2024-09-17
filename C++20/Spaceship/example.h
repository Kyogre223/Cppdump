//
// Created by Lin Kai on 17/9/24.
//

#ifndef CPPDUMP_EXAMPLE_H
#define CPPDUMP_EXAMPLE_H


#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>

struct A {
    int x;
    std::string y;

    auto operator <=> (A const& other) const = default; // OOPS, forgets const here
};



template <typename T, size_t N>
void foo(T (&A)[N]) {
    std::cout << N << '\n';
}

int main() {
    A a{10, "Hello world!\n"};
    A b{20, "Hello world!\n"};
    std::priority_queue<A, std::vector<A>, std::less<A>>pq;
    if (a < b) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    char c[5] = "Hell";
    foo(c);
    return 0;
}


#endif //CPPDUMP_EXAMPLE_H
