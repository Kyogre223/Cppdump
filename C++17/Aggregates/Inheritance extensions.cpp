//
// Created by Lin Kai on 28/10/24.
//

#include <iostream>
#include <vector>


// aggregate examples.
// aggregate initialization means initializing objects that has no
// -user defined constructors / destrucrtors/
// no private or protected member variables and no static members.

struct A {
    int a;
    int b;
};


struct C : public A {
    int c;
};


int main() {

    C obj = {{2, 3}, 4}; // OK


    return 0;
}
