//
// Created by Lin Kai on 3/9/24.
//

#ifndef CPPDUMP_INHERITANCE_OPTIMISATIONS_H
#define CPPDUMP_INHERITANCE_OPTIMISATIONS_H

#include <iostream>

#include <iostream>

struct Base1 {};

struct Base2 {};

struct Derived : public Base1, public Base2 {

};

struct Base3 {
    int a = 2;

    void publicMethod() {
        std::cout << "This is a public method!\n";
    }
private:
    int a2 = 3;
};

struct Base4 {int b = 4; private: int b2 = 5;};

struct Derived2: public Base3, public Base4 {
    int c = 10;
};

// what about private ?

struct Derived3: private Base3, private Base4 {
    void call() {
        std::cout << this->a << '\n';
        this->publicMethod();
    }

};


#endif //CPPDUMP_INHERITANCE_OPTIMISATIONS_H
