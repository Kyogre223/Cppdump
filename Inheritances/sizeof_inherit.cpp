#include <iostream>
#include <vector>
#include <string>

struct A {

    virtual void call() = 0;

    long long x;
};

struct B : public A {
    int y;
    virtual void call() override {
        std::cout << "BCALL\n";
    }
};

int main() {

    B b;
    std::cout << sizeof(B) << '\n';

    return 0;
}
