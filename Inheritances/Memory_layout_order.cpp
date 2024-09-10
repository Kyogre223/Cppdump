#include <iostream>
#include <vector>
#include <string>

// Initialiser is in order
// Dtor is in reverse order
// No assumptions on the memory layout.
struct A {
    A() {
        std::cout << "A\n";
    }
    virtual void call() {
        std::cout << "MyA\n";
    }
    virtual ~A() {
        std::cout << "Adtor\n";
    }

};

struct B {
    B() {
        std::cout << "B\n";
    }
    int x;
    virtual ~B() {
        std::cout << "Bdtor\n";
    }
};


struct C : public A, public B {
    int y;
};
int main() {
    C c;
    A* ptr = &c;
    B* ptr2 = &c;
    C* ptr3 = &c;
    std::cout << "ptr " << ptr << '\n';
    std::cout << "ptr2 " << ptr2 << '\n';
    std::cout << "DIFF " << (char*)ptr2 - (char*)ptr << '\n';
    std::cout << "ptr3 " << ptr3 << '\n';
    return 0;
}