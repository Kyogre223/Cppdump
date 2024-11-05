//
// Created by Lin Kai on 29/10/24.
//

#include <iostream>
#include <vector>


struct MyClass {

    MyClass() {
        std::cout << "Default ctor\n";
    }
    MyClass(MyClass const& other) {
        std::cout << "Copy ctor\n";
    }

    MyClass(MyClass&& other) noexcept {}

    MyClass& operator = (MyClass const& other) {
        return *this;
    }

    MyClass& operator = (MyClass&& other) noexcept {
        return *this;
    }

    ~MyClass() {
        std::cout << "Dtor\n";
    }

};

void foo(MyClass) {
    std::cout << "Inside foo\n";
}

MyClass bar() {

    MyClass s;
    return s;
}

// copy elision happens when passing r values to a function or returning by it.

// C++ 17 makes it compulsory so factory functions work.


int main() {
    foo(MyClass{});
    auto c = bar();



    return 0;
}
