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


struct Base1 {
    Base1() {
        std::cout << "Base1 ctr\n";
    }
    int x;
};

struct Base2 {
    Base2() {
        std::cout << "Base2 ctr\n";
    }
    int y;
};

struct Derived : public Base1, public Base2 {
    int z;
};

int main() {
    Derived d;
    Derived* ptr = &d;
    std::cout << "Derived: " << ptr << '\n';
    std::cout << "Base1: " << static_cast<Base1*>(ptr) << '\n';
    std::cout << "Base2: " << static_cast<Base2*>(ptr) << '\n';
    std::cout << std::addressof(static_cast<Base1*>(ptr)->x) << '\n';
    std::cout << std::addressof(static_cast<Base2*>(ptr)->y) << '\n';
    std::cout << std::addressof(ptr->z) << '\n';
    std::cout << "AGAIN\n";
    return 0;
}