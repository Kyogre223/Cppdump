//
// Created by Lin Kai on 3/9/24.
//

#ifndef CPPDUMP_INHERITANCE_OPTIMISATIONS_H
#define CPPDUMP_INHERITANCE_OPTIMISATIONS_H

#include <iostream>

struct Base1 {};

struct Base2 {};

struct Derived : public Base1, public Base2 {

};

struct Base3 {
    int a = 2;
};

struct Base4 {int b = 4;};

struct Derived2: public Base3, public Base4 {
    int c = 10;
};


#endif //CPPDUMP_INHERITANCE_OPTIMISATIONS_H
