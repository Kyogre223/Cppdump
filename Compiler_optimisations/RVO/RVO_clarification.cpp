//
// Created by Lin Kai on 21/9/24.
//

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>
#include <algorithm>


struct A {
    int x = 2;
    A() {
        std::cout << "default Ctor\n";
    }
    A(int x) {
        std::cout << "Ctor\n";
    }
    A(A const& other) {
        std::cout << "Copy Ctor\n";
    }
    A(A&& other) {
        std::cout << "Move Ctor\n";
    }
    A operator = (A const& other) {
        std::cout << "assignment\n";
        return *this;
    }

    A operator = (A&& other) {
        std::cout << "Move assignment \n";
        return *this;
    }

    friend A operator + (A& other, A& other2);

};


A operator + (A& other, A& other2) {

    A other3 = other.x + other2.x;

    return other3;
}

int main() {
    A a;
    A b;
    A c(a + b);
    A d = a + b;
    return 0;
}