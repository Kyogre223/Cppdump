//
// Created by Lin Kai on 22/9/24.
//

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

// infinite recursion goes on here.
