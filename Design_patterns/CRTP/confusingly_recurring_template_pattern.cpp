//
// Created by Lin Kai on 22/9/24.
//

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <coroutine>
#include <exception>


//
// Incomplete types
// anything that might affect the size of the class cannot be forward declared.


template <typename D>
class B {
public:
    void call() {
        std::cout << "Base class\n";
        static_cast<D*>(this)->call();
    }
};

class D: public B<D> {
public:
    using T = int;

    // void call() {
    //     std::cout << " I am class D!\n";
    // }
};




int main() {
    B<D> d;
    d.call();




    return 0;
}
